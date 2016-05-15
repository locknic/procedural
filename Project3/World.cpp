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
	//spot->setAttenuation(3250.0,1.0,0.0014,0.000007);
	spot->setAttenuation(15.0,1.0,0.15,0.0075);
	spot->setDirection((Ogre::Vector3(0.0, 0.0, 0.0) - Ogre::Vector3(0.0, 0.0, 100.0)).normalisedCopy());
    spot->setSpotlightRange(Ogre::Degree(5),Ogre::Degree(20),0.7f);
	//spot->setCastShadows(false);
	


	mLevelGenerator = new LevelGenerator(this, mSceneManager);
	tank = new Player(this);
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

		//if (mInputHandler->IsKeyDown(OIS::KC_RIGHT))
		//{
		//	//flashLight->yaw(Ogre::Radian(-time * 1));
		//	flashLight->translate(-time * 5, 0, 0, Ogre::Node::TS_LOCAL);
		//}

		//if (mInputHandler->IsKeyDown(OIS::KC_LEFT))
		//{
		//	//flashLight->yaw(Ogre::Radian(time * 1));
		//	flashLight->translate(time * 5, 0, 0, Ogre::Node::TS_LOCAL);
		//}

		//if (mInputHandler->IsKeyDown(OIS::KC_UP))
		//{
		//	flashLight->translate(0,0,-time * 5, Ogre::Node::TS_LOCAL);
		//}
		//if (mInputHandler->IsKeyDown(OIS::KC_DOWN))
		//{
		//	flashLight->translate(0,0,time * 5, Ogre::Node::TS_LOCAL);
		//}
		tank->Think(time, mInputHandler);

		mCamera->setPositionFromGhostPosition(tank->mTank->getOrientation(), tank->mTank->getPosition());
		mCamera->setOrientationFromGhostOrientation(tank->mTank->getOrientation());
	}
}

void World::restartGame()
{
	mSceneManager->getRootSceneNode()->removeAndDestroyAllChildren();

	mLevelGenerator->generateLevel(9,9,10,1);

	//tank->mTank = SceneManager()->getRootSceneNode()->createChildSceneNode();
	tank->restart();
	tank->mTank->setPosition(0,1,0);
	tank->mTank->attachObject(spot);

}

void World::addCollisionObject(OBB *newObject)
{
	mStaticCollisions->push_back(newObject);
}