#include "MainMenu.h"

#include "OgreOverlay.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreTextAreaOverlayElement.h"

#include "World.h"
#include "InputHandler.h"

MainMenu::MainMenu(World *world, InputHandler *input) : mWorld(world), mInputHandler(input)
{
	Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	mOverlay = om.getByName("GameTitle");
	mPlayButtonOverlay = om.getByName("PlayButton");
	mRestartButtonOverlay = om.getByName("RestartButton");
	mExitButtonOverlay= om.getByName("ExitButton");
	optionSelected = 0;
	released = true;

	Ogre::TextAreaOverlayElement *te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("PlayButton/Panel/Text1");
	te->setCaption("> PLAY <");

	Ogre::TextAreaOverlayElement *te2 = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("RestartButton/Panel/Text1");
	te2->setCaption("  RESTART  ");

	Ogre::TextAreaOverlayElement *te3 = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("ExitButton/Panel/Text1");
	te3->setCaption("  EXIT  ");
}

void MainMenu::Think(float time)
{
	if (inMenu)
	{
		if (mInputHandler->IsKeyDown(OIS::KC_DOWN))
		{
			changeOption(1);
		}
		else if (mInputHandler->IsKeyDown(OIS::KC_UP))
		{
			changeOption(-1);
		}
		else
		{
			released = true;
		}

		if (mInputHandler->IsKeyDown(OIS::KC_RETURN))
		{
			if (optionSelected == 0)
			{
				hideMenu();
				inMenu = false;
			}
			else if (optionSelected == 1)
			{
				mWorld->restartGame();
			}
			else if (optionSelected == 2)
			{
				mWorld->exitGame();
			}
		}
	}
	else
	{
		if (mInputHandler->IsKeyDown(OIS::KC_ESCAPE))
		{
			inMenu = true;
			displayMenu();
		}
	}
}

void MainMenu::displayMenu()
{
	mOverlay->show();
	mPlayButtonOverlay->show();
	mRestartButtonOverlay ->show();
	mExitButtonOverlay->show();
}

void MainMenu::hideMenu()
{
	mOverlay->hide();
	mPlayButtonOverlay->hide();
	mRestartButtonOverlay->hide();
	mExitButtonOverlay->hide();
}

void MainMenu::changeOption(int difference)
{
	if (released)
	{
		released = false;

		if (optionSelected + difference >= 0 && optionSelected + difference <= 2)
		{
			optionSelected += difference;

			Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
			Ogre::TextAreaOverlayElement *te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("PlayButton/Panel/Text1");
			Ogre::TextAreaOverlayElement *te2 = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("RestartButton/Panel/Text1");
			Ogre::TextAreaOverlayElement *te3 = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("ExitButton/Panel/Text1");
		
			if (optionSelected == 0)
			{
				te->setCaption("> PLAY <");
				te2->setCaption("  RESTART  ");
				te3->setCaption("  EXIT  ");
			}
			else if (optionSelected == 1)
			{
				te->setCaption("  PLAY  ");
				te2->setCaption("> RESTART <");
				te3->setCaption("  EXIT  ");
			}
			else
			{
				te->setCaption("  PLAY  ");
				te2->setCaption("  RESTART  ");
				te3->setCaption("> EXIT <");
			}
		}
	}
}