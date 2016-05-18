#pragma once

#include <ois/ois.h>
#include "Ogre.h"

class World;
class InputHandler;
class OBB;

class Player
{
public:
	Player(World *world);
	~Player(void);
	void Think(float time, InputHandler *mInputHandler);

	Ogre::SceneManager *SceneManager() { return mSceneManager; }

	void restart();
	Ogre::SceneNode *mTank;
	Ogre::Entity *tankEntity;

private:

	World *mWorld;
	
	int i;
	Ogre::SceneManager *mSceneManager;
	Ogre::Real mRotate;
	Ogre::Real mMove;
	Ogre::SceneNode* mCamNode;
	Ogre::Vector3 mDirection;
	
	OBB  *playerOBB;
};