#include "OgreMatrix3.h"
#include "OgreVector3.h"
#include "OgreVector4.h"

// Forward delcarations of Ogre classes.  Note the Ogre namespace!
namespace Ogre {
    class SceneNode;
    class SceneManager;
	class Entity;
}

// Forward delcarations of our own classes
class World;
class Wall;

class Room
{
public:
    Room(Ogre::SceneManager *sceneManager, Ogre::Vector4 doors, Ogre::Vector3 position);

	Ogre::Entity *floorEnt;
	Ogre::SceneNode *floor;
	Wall *nWall;
	Wall *eWall;
	Wall *wWall;
	Wall *sWall;
	Ogre::Entity *furnEnt;
	Ogre::SceneNode *furn;
	void getPiano(Ogre::SceneManager *sceneManager, Ogre::Vector3 position);

protected:
	Ogre::SceneManager *mSceneManager;
	World *mWorld;
};