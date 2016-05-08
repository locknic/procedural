#include "Monster.h"

#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "Ogre.h"

#include "World.h"

Monster::Monster(World *world) : mWorld(world)
{
	ent1 = world->SceneManager()->createEntity("DrawCall_640.001.mesh");
	mMonster = world->SceneManager()->getRootSceneNode()->createChildSceneNode();
	mMonster->attachObject(ent1);
	mMonster->scale(0.60,0.60,0.60);
	mMonster->rotate(Ogre::Vector3::NEGATIVE_UNIT_Z,Ogre::Degree(180),Ogre::Node::TS_WORLD );
}

Monster::~Monster()
{
    // Clean up after yourself ...
}

void 
	Monster::Think(float time, Ogre::Vector3 pos)
{

	Ogre::Vector3 o =  pos - mMonster->getPosition();
	//Ogre::Quaternion q = ori - mMonster->getOrientation(); 

	mMonster->translate(
            (o.x * 1 * time),
            (0),
            (o.z * 1 * time),
           Ogre::Node::TS_WORLD);
	
	mMonster->lookAt(Ogre::Vector3(pos.x,mMonster->getPosition().y,pos.z), Ogre::Node::TS_WORLD, Ogre::Vector3::NEGATIVE_UNIT_Z);
}

