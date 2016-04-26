#ifndef __World_h_
#define __World_h_

// Forward delcarations of Ogre classes.  Note the Ogre namespace!
namespace Ogre {
    class SceneNode;
    class SceneManager;
	class Entity;
}

// Forward delcarations of our own classes
class PongCamera;
class InputHandler;


class World
{
public:
	
    World(Ogre::SceneManager *sceneManager, InputHandler *input);

    // You'll want various methods to access & change your world here
    void ResetVelocity();
    void Think(float time);
	void addCamera(PongCamera *c) { mCamera = c; }

	Ogre::SceneManager *SceneManager() { return mSceneManager; }


protected:


	Ogre::SceneManager *mSceneManager;

	InputHandler *mInputHandler;
	PongCamera *mCamera;

	// Here is where you keep all your world data.
	//  You probably want to use containers (arrays / lists / classes / etc) to ogranize them, 
	//    instead of a whole list of variables.  

	Ogre::SceneNode *mCoinNode;
	Ogre::SceneNode *mCoinNode2;
	Ogre::SceneNode *mLeftPaddle;
	Ogre::SceneNode *mRightPaddle;
	Ogre::SceneNode *NPaddle;
	Ogre::SceneNode *mCeiling;
	Ogre::SceneNode *mFloor;
	Ogre::Entity *NPaddleEnt;
	Ogre::Entity *coinEnt;
	Ogre::Entity *coinEnt2;
	Ogre::Entity *LPaddleEnt;
	Ogre::Entity *RPaddleEnt;

};

#endif