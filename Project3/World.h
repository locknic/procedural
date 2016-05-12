#ifndef __World_h_
#define __World_h_

// Forward delcarations of Ogre classes.  Note the Ogre namespace!
namespace Ogre {
    class SceneNode;
    class SceneManager;
	class Entity;
	class Light;
}

// Forward delcarations of our own classes
class GhostCamera;
class InputHandler;
class MainMenu;
class Wall;
class Room;
class LevelGenerator;
class Player;
class OBB;

class World
{
public:
	
    World(Ogre::SceneManager *sceneManager, InputHandler *input);

    // You'll want various methods to access & change your world here
    void Think(float time);
	void addCamera(GhostCamera *c) { mCamera = c; }
	bool getKeepGoing() { return keepGoing; }
	void restartGame();
	void exitGame(){ keepGoing = false; }
	GhostCamera* getCamera() { return mCamera; }
	void addCollisionObject(OBB *newObject);

	Ogre::SceneManager *SceneManager() { return mSceneManager; }
	Ogre::SceneNode *flashLight;
	Player *tank;


public:


	Ogre::SceneManager *mSceneManager;

	InputHandler *mInputHandler;
	GhostCamera *mCamera;
	MainMenu *mMainMenu;
	LevelGenerator *mLevelGenerator;

private:
	
	bool keepGoing;

	Ogre::Light *spot;

};

#endif