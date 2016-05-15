#include "Player.h"
#include "World.h"
#include "InputHandler.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "Ogre.h"
#include "OBB.h"
#include "MainMenu.h"
Player::Player(World *world) : mWorld(world)
{

}


void 
Player::restart() 
{
	tankEntity = mWorld->SceneManager()->createEntity("DrawCall_640.001.mesh");
	mTank = mWorld->SceneManager()->getRootSceneNode()->createChildSceneNode();
	mTank->attachObject(tankEntity);
	mTank->setPosition(0, 1, 20);
	mTank->scale(.5,.5,.5);
	mTank->setVisible(false);
	playerOBB = new OBB(tankEntity->getBoundingBox(), mTank->getPosition(), mTank->getOrientation());
}

Player::~Player(void)
{
}


void 
Player::Think(float time, InputHandler *mInputHandler)
{

	const float RADIANS_PER_SECOND = 1;
	const float SPEED = 7;

	mInputHandler->mMouse->capture();

	int mx =mInputHandler->mMouse->getMouseState().X.rel;
	int my = mInputHandler->mMouse->getMouseState().Y.rel;
	
	//The bigger the # you divide by, the slower the move
	mTank->yaw((Ogre::Degree) mx*-10 / 60, Ogre::Node::TS_WORLD);

	Ogre::Radian oldPitch = mTank->getOrientation().getPitch();
	Ogre::Radian newPitch = Ogre::Math::Abs((Ogre::Degree)(my*-10 / 60) + oldPitch);

	if(newPitch < Ogre::Radian(Ogre::Math::PI/2)) {
		mTank->pitch((Ogre::Degree) my*-10 / 60);
	}


	if (mInputHandler->IsKeyDown(OIS::KC_RIGHT))
	{
		mTank->translate(time * SPEED, 0, 0, Ogre::Node::TS_LOCAL);
	}
	else if (mInputHandler->IsKeyDown(OIS::KC_LEFT))
	{
		mTank->translate(-time * SPEED, 0, 0, Ogre::Node::TS_LOCAL);
	}
	if (mInputHandler->IsKeyDown(OIS::KC_UP))
	{
		mTank->translate(0, 0, -time * SPEED, Ogre::Node::TS_LOCAL);
	}
	else if (mInputHandler->IsKeyDown(OIS::KC_DOWN))
	{
		mTank->translate(0, 0, time * SPEED, Ogre::Node::TS_LOCAL);
	}

	playerOBB->setPosition(mTank->getPosition());
	playerOBB->setOrientation(mTank->getOrientation());


	if (mWorld->mStaticCollisions->begin() != mWorld->mStaticCollisions->end())
	{
		for(std::vector<OBB*>::iterator it = mWorld->mStaticCollisions->begin(); it != mWorld->mStaticCollisions->end(); ++it) 
		{
			Ogre::Vector3 moveVector;

			if ((*it)->collides(playerOBB, moveVector))
			{

			}
			
			mTank->translate(moveVector);
		}
	}


	//Quick and dirty: Fixes issue of moving up if aiming up. If ground not at 0, change y component to be whatever the ground is at.
	mTank->setPosition(mTank->getPosition().x, 1, mTank->getPosition().z);

}