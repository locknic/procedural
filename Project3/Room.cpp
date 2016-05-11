#include "OgreCamera.h"
#include "Room.h"
#include "World.h"
#include "Wall.h"
#include "OgreVector3.h"

#include "Ogre.h"
#include "OgreMath.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreFontManager.h"
#include "OgreTextAreaOverlayElement.h"
    

Room::Room(Ogre::SceneManager *sceneManager, Ogre::Vector4 doors, Ogre::Vector3 position)  : mSceneManager(sceneManager)
{
	nWall = new Wall(mSceneManager, doors.x, position, Ogre::Radian(0));
	eWall = new Wall(mSceneManager, doors.y, position, Ogre::Radian(Ogre::Math::PI/2));
	sWall = new Wall(mSceneManager, doors.z, position, Ogre::Radian(Ogre::Math::PI));
	wWall = new Wall(mSceneManager, doors.w, position, Ogre::Radian(Ogre::Math::PI/-2));

	floorEnt = mSceneManager->createEntity("Floor.mesh");
	floor = mSceneManager->getRootSceneNode()->createChildSceneNode();
	floor->attachObject(floorEnt);
	floor->scale(5,5,5);
	floor->setPosition(position);
	getPiano(sceneManager, position);
}
void
	Room::getPiano(Ogre::SceneManager *sceneManager, Ogre::Vector3 position)
{
	furnEnt = mSceneManager->createEntity("1.mesh");
	furn = mSceneManager->getRootSceneNode()->createChildSceneNode();
	furn->attachObject(furnEnt);
	furn->scale(.75, .75, .75);
	furn->rotate(Ogre::Vector3::UNIT_X,Ogre::Degree(90),Ogre::Node::TS_WORLD );
}

// get desk , chair, bed etc....

