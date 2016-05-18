// My header file.  This should go first!
#include "World.h"

// Ogre header files
#include "Ogre.h"
#include "OgreMath.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreFontManager.h"
#include "OgreTextAreaOverlayElement.h"

// IOS (Input system) header files

#include <ois/ois.h>

#include <stdlib.h>
#include <vector>

// Other input files for my project
#include "Camera.h"
#include "Wall.h"
#include "Room.h"
#include "InputHandler.h"
#include "MainMenu.h"
#include "LevelGenerator.h"
#include "Player.h"
#include "OBB.h"
#include "Sound.h"
#include <SDL_mixer.h>


World::World(Ogre::SceneManager *sceneManager, InputHandler *input)   : mSceneManager(sceneManager), mInputHandler(input)
{

	mSceneManager->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));
    mSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	// Yeah, this should be done automatically for all fonts referenced in an overlay file.
	//  But there is a bug in the OGRE code so we need to do it manually.
	Ogre::ResourceManager::ResourceMapIterator iter = Ogre::FontManager::getSingleton().getResourceIterator();
	while (iter.hasMoreElements()) 
	{ 
		iter.getNext()->load(); 
	}

	mStaticCollisions = new std::vector<OBB*>;

	spot = mSceneManager->createLight("Flashlight");
    spot->setType(Ogre::Light::LT_SPOTLIGHT);
    spot->setDiffuseColour(1.0, 1.0, 1.0);
	spot->setSpecularColour(1.0, 1.0, 1.0);
	spot->setPosition(0, .1, 5);
	spot->setAttenuation(100.0,0.5,0.045,0.0075);
	spot->setDirection((Ogre::Vector3(0.0, 0.0, 0.0) - Ogre::Vector3(0.0, 0.0, 100.0)).normalisedCopy());
    spot->setSpotlightRange(Ogre::Degree(5),Ogre::Degree(20),0.7f);
	SoundBank *s = new SoundBank();
	s->setup();
	s->openFile("ExtremeHorror.wav", "monster", 0);
	s->fadeIn("monster", 0, true);
	s->openFile("Heart.wav", "heart", 0);
	s->fadeIn("heart", 0, true);
	
	s->setEnableSound(true);
	mLevelGenerator = new LevelGenerator(this, mSceneManager);
	tank = new Player(this);
	restartGame();
	mMainMenu = new MainMenu(this, mInputHandler);
	mMainMenu->displayMenu();
	keepGoing = true;
	light = true;
	k = 20;
	i = 0;
	life = 100;
	Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	mOverlay = om.getByName("Battery");
	text = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("Battery/Panel/Text1");
	released = true;
}

void 
World::Think(float time)
{
	mMainMenu->Think(time);
	mOverlay->show();
	std::string lifes = std::to_string((int)life);
	std::string final = "Battery: " +  lifes + "%" ;

	text->setCaption(final);
	if (!mMainMenu->getInMenu())
	{
		mLevelGenerator->Think(time);
		if (mInputHandler->IsKeyDown(OIS::KC_F)) 
		{
			if (released)
			{
				i = k;
				if (light == false) 
				{
					if (life > 0) 
					{
					light = true;
					} 
					else 
					{
						light = false;
					}
				} 
				else 
				{
					light = false;
				}
				released = false;
			}
		}
		else
		{
			released = true;
		}
		k++;
		if (light == false && life < 100 ) 
		{
			life += time * 20;
		} 
		else if (light == true) 
		{
			if (life > 0) 
			{
			life -= 40 * time;
			} 
			else 
			{
				life = 0;
			}
		}
		if (life <= 0) 
		{
			light = false;
		}

		spot->setVisible(light);
		tank->Think(time, mInputHandler);

		mCamera->setPositionFromGhostPosition(tank->mTank->getOrientation(), tank->mTank->getPosition());
		mCamera->setOrientationFromGhostOrientation(tank->mTank->getOrientation());
	}
}

void World::restartGame()
{
	mSceneManager->getRootSceneNode()->removeAndDestroyAllChildren();

	mLevelGenerator->generateLevel(9,9,10,1);
	tank->restart();
	tank->mTank->setPosition(0,1,0);
	tank->mTank->attachObject(spot);

}

void World::addCollisionObject(OBB *newObject)
{
	mStaticCollisions->push_back(newObject);
}