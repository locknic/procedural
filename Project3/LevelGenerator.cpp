#include "LevelGenerator.h"

#include <stdlib.h>
#include <time.h>

#include "OgreSceneManager.h"
#include "OgreMeshManager.h"
#include "OgrePlane.h"
#include "OgreEntity.h"
#include "OgreSceneNode.h"

#include "World.h"
#include "Room.h"

LevelGenerator::LevelGenerator(World *world, Ogre::SceneManager *sceneManager) : mWorld(world), mSceneManager(sceneManager)
{
	srand((unsigned)time(0));

	mRooms = new bool[ROWS * COLUMNS];
	for (int x = 0; x < ROWS; x++)
	{
		for (int z = 0; z < COLUMNS; z++)
		{
			setArrayVaueAt(0, x, z);
		}
	}

	int midRow = (ROWS - 1) / 2;
	int midColumn = (COLUMNS - 1) / 2;

	setArrayVaueAt(1, midRow, midColumn);
	setArrayVaueAt(1, midRow - 1, midColumn);
	setArrayVaueAt(1, midRow + 1, midColumn);
	setArrayVaueAt(1, midRow, midColumn - 1);
	setArrayVaueAt(1, midRow, midColumn + 1);

	generateBranches(midRow - 1, midColumn);
	generateBranches(midRow + 1, midColumn);
	generateBranches(midRow, midColumn - 1);
	generateBranches(midRow, midColumn + 1);

	generateModels();
}

void LevelGenerator::generateBranches(int currentRow, int currentColumn)
{
	generateRoom(currentRow + 1, currentColumn);
	generateRoom(currentRow - 1, currentColumn);
	generateRoom(currentRow, currentColumn + 1);
	generateRoom(currentRow, currentColumn - 1);
}

void LevelGenerator::generateRoom(int currentRow, int currentColumn)
{
	if (!getArrayVaueAt(currentRow, currentColumn))
	{
		if (rand() % 100 < 30)
		{
			setArrayVaueAt(1, currentRow, currentColumn);
			generateBranches(currentRow, currentColumn);
		}
	}
}

void LevelGenerator::generateModels()
{


	Ogre::Plane plane2(Ogre::Vector3::NEGATIVE_UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
 "roof",
  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
  plane2, 
  1500, 1500, 20, 20, 
  true, 
  1, 5, 5, 
  Ogre::Vector3::UNIT_Z);
	Ogre::Entity* roofEntity = mSceneManager->createEntity("roof");
	Ogre::SceneNode* roofNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
	roofNode->attachObject(roofEntity);
	roofNode->setPosition(0, 2.5, 0);
	roofEntity->setMaterialName("SouthWall");

	for (int x = 0; x < ROWS; x++)
	{
		for (int z = 0; z < COLUMNS; z++)
		{
			if (getArrayVaueAt(x, z))
			{
				bool left, right, up, down;
				left = right = up = down = 0;

				if (x - 1 >= 0 & x - 1 < ROWS)
				{
					left = getArrayVaueAt(x - 1, z);
				}
				if (x + 1 >= 0 & x + 1 < ROWS)
				{
					right = getArrayVaueAt(x + 1, z);
				}
				if (z - 1 >= 0 & z - 1 < COLUMNS)
				{
					up = getArrayVaueAt(x, z - 1);
				}
				if (z + 1 >= 0 & z + 1 < COLUMNS)
				{
					down = getArrayVaueAt(x, z + 1);
				}
				new Room(mSceneManager, Ogre::Vector4(up, left, down, right), Ogre::Vector3(x * ROOM_WIDTH - ((ROWS - 1) / 2 * ROOM_WIDTH), 0, z * ROOM_WIDTH - ((COLUMNS - 1) / 2 * ROOM_WIDTH)));
			}
		}
	}
}

int LevelGenerator::findArrayPosition(int currentRow, int currentColumn)
{
	return currentRow * COLUMNS + currentColumn;
}

bool LevelGenerator::getArrayVaueAt(int currentRow, int currentColumn)
{
	return mRooms[findArrayPosition(currentRow, currentColumn)];
}

void LevelGenerator::setArrayVaueAt(bool value, int currentRow, int currentColumn)
{
	mRooms[findArrayPosition(currentRow, currentColumn)] = value;
}