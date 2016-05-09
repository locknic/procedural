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

// Other input files for my project
#include "Camera.h"
#include "Wall.h"
#include "Room.h"
#include "InputHandler.h"
#include "MainMenu.h"
#include "LevelGenerator.h"

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

	
	spot = mSceneManager->createLight("Flashlight");
    spot->setType(Ogre::Light::LT_SPOTLIGHT);
    spot->setDiffuseColour(1.0, 1.0, 1.0);
	spot->setSpecularColour(1.0, 1.0, 1.0);
	spot->setPosition(0, .1, 5);
	//spot->setAttenuation(3250.0,1.0,0.0014,0.000007);
	spot->setAttenuation(15.0,1.0,0.15,0.0075);
	spot->setDirection((Ogre::Vector3(0.0, 0.0, 0.0) - Ogre::Vector3(0.0, 0.0, 100.0)).normalisedCopy());
    spot->setSpotlightRange(Ogre::Degree(12),Ogre::Degree(45),0.7f);
	//spot->setCastShadows(false);
	


	mLevelGenerator = new LevelGenerator(this, mSceneManager);

	restartGame();

	mMainMenu = new MainMenu(this, mInputHandler);
	mMainMenu->displayMenu();

	keepGoing = true;
}

void 
World::Think(float time)
{
	mMainMenu->Think(time);

	if (!mMainMenu->getInMenu())
	{
		mLevelGenerator->Think(time);

		if (mInputHandler->IsKeyDown(OIS::KC_RIGHT))
		{
			flashLight->yaw(Ogre::Radian(-time * 1));
		}

		if (mInputHandler->IsKeyDown(OIS::KC_LEFT))
		{
			flashLight->yaw(Ogre::Radian(time * 1));
		}

		if (mInputHandler->IsKeyDown(OIS::KC_UP))
		{
			flashLight->translate(0,0,-time * 5, Ogre::Node::TS_LOCAL);
		}
		if (mInputHandler->IsKeyDown(OIS::KC_DOWN))
		{
			flashLight->translate(0,0,time * 5, Ogre::Node::TS_LOCAL);
		}

		mCamera->setPositionFromGhostPosition(flashLight->getOrientation(), flashLight->getPosition());
		mCamera->setOrientationFromGhostOrientation(flashLight->getOrientation());
	}
}

void World::restartGame()
{
	mSceneManager->getRootSceneNode()->removeAndDestroyAllChildren();

	mLevelGenerator->generateLevel(9,9,10,1);

	flashLight = SceneManager()->getRootSceneNode()->createChildSceneNode();
	flashLight->setPosition(0,1,0);
	flashLight->attachObject(spot);

}