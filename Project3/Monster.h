#ifndef __Monster_h_
#define __Monster_h_


namespace Ogre {
    class SceneNode;
    class SceneManager;
	class Vector3;
	class Quaternion;
	class Entity;
	class TextAreaOverlayElement;
}

class World;


class Monster 
{

public:
    // You may want to add parameters to the AI Manager constructor
	Monster(World *world);
	~Monster();

    // Go through all of the AIs, and call think on each one
    void Think(float time, Ogre::Vector3 pos);

protected:
	World *mWorld;
	
    // Probablay want a list of individual AI classes here ...
public:
Ogre::SceneNode *mMonster;
Ogre::Entity *ent1;
};
#endif