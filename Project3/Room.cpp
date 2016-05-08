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
}
