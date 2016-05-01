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
#include "InputHandler.h"

World::World(Ogre::SceneManager *sceneManager, InputHandler *input)   : mSceneManager(sceneManager), mInputHandler(input)
{

	mSceneManager->setAmbientLight(Ogre::ColourValue(1,1,1));

	// Yeah, this should be done automatically for all fonts referenced in an overlay file.
	//  But there is a bug in the OGRE code so we need to do it manually.
	Ogre::ResourceManager::ResourceMapIterator iter = Ogre::FontManager::getSingleton().getResourceIterator();
	while (iter.hasMoreElements()) 
	{ 
		iter.getNext()->load(); 
	}


	Ogre::Entity *NorthWall = SceneManager()->createEntity("NorthWall.mesh");
	Ogre::Entity *EastWall = SceneManager()->createEntity("EastWall.mesh");
	Ogre::Entity *SouthWall = SceneManager()->createEntity("SouthWall.mesh");
	Ogre::Entity *WestWall = SceneManager()->createEntity("WestWall.mesh");

	Ogre::SceneNode *nWall = SceneManager()->getRootSceneNode()->createChildSceneNode();
	nWall->attachObject(NorthWall);
	nWall->setPosition(0,0,0);
	nWall->scale(1,1,1);

	Ogre::SceneNode *eWall = SceneManager()->getRootSceneNode()->createChildSceneNode();
	eWall->attachObject(EastWall);
	eWall->setPosition(0,0,0);
	eWall->scale(1,1,1);

	Ogre::SceneNode *sWall = SceneManager()->getRootSceneNode()->createChildSceneNode();
	sWall->attachObject(SouthWall);
	sWall->setPosition(0,0,0);

	Ogre::SceneNode *wWall = SceneManager()->getRootSceneNode()->createChildSceneNode();
	wWall->attachObject(WestWall);
	wWall->setPosition(0,0,0);

	// Now we will show the sample overlay.  Look in the file Content/Overlays/Example to
	// see how this overlay is defined
	Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	Ogre::Overlay *overly = om.getByName("Sample");
	overly->show();
}

void 
World::Think(float time)
{
	mCamera->setPosition(Ogre::Vector3(0, 0, 0));
	mCamera->lookAt(Ogre::Vector3(1.0, 0, 500));

	if (mInputHandler->IsKeyDown(OIS::KC_RIGHT))
	{
		mCamera->yaw(Ogre::Degree(3 * time));
	}
}


