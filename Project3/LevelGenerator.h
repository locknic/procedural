#ifndef __LevelGenerator_h_
#define __LevelGenerator_h_

namespace Ogre
{
	class SceneManager;
}

class World;

class LevelGenerator
{
public:
	LevelGenerator(World *world, Ogre::SceneManager *sceneManager);
	
private:
	void generateBranches(int currentRow, int currentColumn);
	void generateRoom(int currentRow, int currentColumn);
	void generateModels();
	int findArrayPosition(int currentRow, int currentColumn);
	bool getArrayVaueAt(int currentRow, int currentColumn);
	void LevelGenerator::setArrayVaueAt(bool value, int currentRow, int currentColumn);

	World *mWorld;
	Ogre::SceneManager *mSceneManager;

	// ROWS AND COLUMNS SHOULD BE ODD NUMBER
	static const int ROWS = 9;
	static const int COLUMNS = 9;
	static const int ROOM_WIDTH = 10;

	bool *mRooms;

};

#endif