#include "OgreCamera.h"
#include "Room.h"
#include "World.h"
#include "Wall.h"
#include "OgreVector3.h"
#include "OBB.h"

#include "Ogre.h"
#include "OgreMath.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreFontManager.h"
#include "OgreTextAreaOverlayElement.h"
    

Room::Room(World *world, Ogre::SceneManager *sceneManager, Ogre::Vector4 doors, Ogre::Vector3 position)  : mWorld(world), mSceneManager(sceneManager)
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

	leftWall = mSceneManager->createEntity("LeftWall.mesh");
	lWall = mSceneManager->getRootSceneNode()->createChildSceneNode();
	lWall->attachObject(leftWall); 
	lWall->setVisible(false);

	obj1 = new OBB(leftWall->getBoundingBox(), nWall->wall[0]->getPosition(),nWall->wall[0]->getOrientation());
	obj2 = new OBB(nWall->rightWall->getBoundingBox(), nWall->wall[1]->getPosition(),nWall->wall[1]->getOrientation());
	obj3 = new OBB(nWall->upper->getBoundingBox(), nWall->wall[2]->getPosition(),nWall->wall[2]->getOrientation());

	if (doors.x) {
		obj4 = new OBB(nWall->doorWay->getBoundingBox(), nWall->wall[3]->getPosition(),nWall->wall[3]->getOrientation());
	} else {
		obj4 = new OBB(nWall->doorFill->getBoundingBox(), nWall->wall[3]->getPosition(),nWall->wall[3]->getOrientation());
	}
	
	obj5 = new OBB(leftWall->getBoundingBox() , eWall->wall[0]->getPosition(),eWall->wall[0]->getOrientation());
	obj6 = new OBB(eWall->rightWall->getBoundingBox(), eWall->wall[1]->getPosition(),eWall->wall[1]->getOrientation());
	obj7 = new OBB(eWall->upper->getBoundingBox(), eWall->wall[2]->getPosition(),eWall->wall[2]->getOrientation());

	if (doors.y) {
		obj8 = new OBB(eWall->doorWay->getBoundingBox(), eWall->wall[3]->getPosition(),eWall->wall[3]->getOrientation());
	} else {
		obj8 = new OBB(eWall->doorFill->getBoundingBox(), eWall->wall[3]->getPosition(),eWall->wall[3]->getOrientation());
	}

	obj9 = new OBB(leftWall->getBoundingBox(), sWall->wall[0]->getPosition(),sWall->wall[0]->getOrientation());
	obj10 = new OBB(sWall->rightWall->getBoundingBox(),sWall->wall[1]->getPosition(),sWall->wall[1]->getOrientation());
	obj11 = new OBB(sWall->upper->getBoundingBox(), sWall->wall[2]->getPosition(),sWall->wall[2]->getOrientation());

	if (doors.z) {
		obj12 = new OBB(sWall->doorWay->getBoundingBox(), sWall->wall[3]->getPosition(),sWall->wall[3]->getOrientation());
	} else {
		obj12 = new OBB(sWall->doorFill->getBoundingBox(),sWall->wall[3]->getPosition(),sWall->wall[3]->getOrientation());
	}

	obj13 = new OBB(leftWall->getBoundingBox(), wWall->wall[0]->getPosition(),wWall->wall[0]->getOrientation());
	obj14 = new OBB(wWall->rightWall->getBoundingBox(), wWall->wall[1]->getPosition(),wWall->wall[1]->getOrientation());
	obj15 = new OBB(wWall->upper->getBoundingBox(), wWall->wall[2]->getPosition(),wWall->wall[2]->getOrientation());

	if (doors.w) {
		obj16 = new OBB(wWall->doorWay->getBoundingBox(), wWall->wall[3]->getPosition(),wWall->wall[3]->getOrientation());
	} else {
		obj16 = new OBB(wWall->doorFill->getBoundingBox(), wWall->wall[3]->getPosition(),wWall->wall[3]->getOrientation());
	}

	obj1->setScale(Ogre::Vector3(5, 5, 5));
	obj2->setScale(Ogre::Vector3(5, 5, 5));
	obj2->setScale(Ogre::Vector3(5, 5, 5));
	obj2->setScale(Ogre::Vector3(5, 5, 5));
	obj2->setScale(Ogre::Vector3(5, 5, 5));
	obj2->setScale(Ogre::Vector3(5, 5, 5));
	obj2->setScale(Ogre::Vector3(5, 5, 5));
	obj2->setScale(Ogre::Vector3(5, 5, 5));
	obj2->setScale(Ogre::Vector3(5, 5, 5));
	obj2->setScale(Ogre::Vector3(5, 5, 5));
	obj2->setScale(Ogre::Vector3(5, 5, 5));
	obj2->setScale(Ogre::Vector3(5, 5, 5));
	obj2->setScale(Ogre::Vector3(5, 5, 5));
	obj2->setScale(Ogre::Vector3(5, 5, 5));
	obj2->setScale(Ogre::Vector3(5, 5, 5));
	obj2->setScale(Ogre::Vector3(5, 5, 5));

	mWorld->addCollisionObject(obj1);
	mWorld->addCollisionObject(obj2);
	mWorld->addCollisionObject(obj3);
	mWorld->addCollisionObject(obj4);
	mWorld->addCollisionObject(obj5);
	mWorld->addCollisionObject(obj6);
	mWorld->addCollisionObject(obj7);
	mWorld->addCollisionObject(obj8);
	mWorld->addCollisionObject(obj9);
	mWorld->addCollisionObject(obj10);
	mWorld->addCollisionObject(obj11);
	mWorld->addCollisionObject(obj12);
	mWorld->addCollisionObject(obj13);
	mWorld->addCollisionObject(obj14);
	mWorld->addCollisionObject(obj15);
	mWorld->addCollisionObject(obj16);

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
	furn->setPosition(3, 0, 3);
	obj1 = new OBB(furnEnt->getBoundingBox(), furn->getPosition(), furn->getOrientation());
	obj1->setScale(Ogre::Vector3(.75,.75,.75));
	mWorld->addCollisionObject(obj1);
}

// get desk , chair, bed etc....

