// My header file.  This should go first!
#include "World.h"

// Ogre header files
#include "Ogre.h"
#include "OgreMath.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreFontManager.h"
#include "OgreTextAreaOverlayElement.h"

// IOS (Input system) header files

#include <ois/ois.h>

// Other input files for my project
#include "Camera.h"
#include "InputHandler.h"

int p1Score = 0;
int p2Score = 0;
Ogre::Vector3 velocity1;
Ogre::Vector3 velocity2;
Ogre::Vector3 padV;


World::World(Ogre::SceneManager *sceneManager, InputHandler *input)   : mSceneManager(sceneManager), mInputHandler(input)
{

	// Global illumination for now.  Adding individual light sources will make you scene look more realistic
	mSceneManager->setAmbientLight(Ogre::ColourValue(1,1,1));

	// First, we create a scene node, and attach a model to it.  coin.mesh is defined in the Content directory,
	//  under models.  Note that you should probably place all of this creation code into a separate method (or methods)
	//  for your final game
	Ogre::Entity *ent1 =SceneManager()->createEntity("Sphere.mesh");
	coinEnt = ent1;
	mCoinNode = SceneManager()->getRootSceneNode()->createChildSceneNode();
	mCoinNode->attachObject(ent1);
	mCoinNode->setPosition(-30,0,0);


	Ogre::Entity *ent4 =SceneManager()->createEntity("Sphere.mesh");
	coinEnt2 = ent4;
	mCoinNode2 = SceneManager()->getRootSceneNode()->createChildSceneNode();
	mCoinNode2->attachObject(ent4);
	mCoinNode2->setPosition(30,0,0);


	// Create paddle object (hopefully)
	Ogre::Entity *ent2 = SceneManager()->createEntity("PaddleModel.mesh");
	LPaddleEnt = ent2;
	mLeftPaddle = SceneManager()->getRootSceneNode()->createChildSceneNode();
	mLeftPaddle->attachObject(ent2);
	mLeftPaddle->setPosition(45,0,0);

	//Second paddle object
	Ogre::Entity *ent3 = SceneManager()->createEntity("PaddleModel.mesh");
	RPaddleEnt = ent3;
	mRightPaddle = SceneManager()->getRootSceneNode()->createChildSceneNode();
	mRightPaddle->attachObject(ent3);
	mRightPaddle->setPosition(-45, 0, 0);


	//Neutral paddle
	Ogre::Entity *ent5 = SceneManager()->createEntity("PaddleModel.mesh");
	NPaddleEnt = ent5;
	NPaddle = SceneManager()->getRootSceneNode()->createChildSceneNode();
	NPaddle->attachObject(ent5);
	NPaddle->setPosition(0, 0, 0);

	// Now that we have a scene node, we can move, scale and rotate it as we please.  We'll scale this up a smidge
	// just as an example.  
	//   (take a look at the header file for Ogre::SceneNode -- a good IDE is your friend, here)

	mCoinNode->scale(1.5,1.5,1.5);
	mCoinNode2->scale(1.5,1.5,1.5);
	mLeftPaddle->scale(2,2,2);
	mRightPaddle->scale(2,2,2);

	// Yeah, this should be done automatically for all fonts referenced in an overlay file.
	//  But there is a bug in the OGRE code so we need to do it manually.
	Ogre::ResourceManager::ResourceMapIterator iter = Ogre::FontManager::getSingleton().getResourceIterator();
	while (iter.hasMoreElements()) 
	{ 
		iter.getNext()->load(); 
	}

	// Now we will show the sample overlay.  Look in the file Content/Overlays/Example to
	// see how this overlay is defined
	Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	Ogre::Overlay *overly = om.getByName("Sample");
	overly->show();

	velocity1 = Ogre::Vector3(70, 7, 0);
	velocity2 = Ogre::Vector3(-50, 15, 0);
	padV = Ogre::Vector3(0, -10, 0);
}

void
World::ResetVelocity(){
	velocity1 = Ogre::Vector3(60, 7, 0);
	velocity2 = Ogre::Vector3(-50, 15, 0);
}

void 
World::Think(float time)
{
	const float RADIANS_PER_SECOND = 0.5;
	const float CoinSpeed = 30;
	Ogre::Vector3 pos = mCoinNode->getPosition();
	Ogre::Vector3 pos2 = mCoinNode2->getPosition();
	Ogre::Vector3 padPos = mRightPaddle->getPosition();

	if(pos.y >= 40){
		velocity1.y *= -1;
		mCoinNode->translate(velocity1*time);
	}
	if(pos2.y >= 40){
		velocity2.y *= -1;
		mCoinNode2->translate(velocity2*time);
	}

	if(pos.y <= -40){
		velocity1.y *= -1;
		mCoinNode->translate(velocity1*time);
	}
	if(pos2.y <= -40){
		velocity2.y *= -1;
		mCoinNode2->translate(velocity2*time);
	}
	mCoinNode->translate(velocity1*time);
	mCoinNode2->translate(velocity2*time);

	if(NPaddle->getPosition().y >= 40 || NPaddle->getPosition().y <= -40){
		padV.y *= -1;
	}
	NPaddle->translate(padV*time);

	// This is a pretty silly think method, but it gives you some ideas about how
	//  to proceed.  The single object will rotate

	 //mCoinNode->pitch(Ogre::Radian(time * RADIANS_PER_SECOND));

	//Scoring
	
	if(pos.x < -50){
		p1Score++;
		if(velocity2.x == 0){
			mCoinNode->setPosition(-30,0,0);
			mCoinNode2->setPosition(30, 0, 0);
			ResetVelocity();
		}
		else{
			mCoinNode->setPosition(0,100,0);
			velocity1 *= 0;
			
		}
	}
	if(pos.x > 50){
		p2Score++;
		if(velocity2.x == 0){
			mCoinNode->setPosition(-30,0,0);
			mCoinNode2->setPosition(30, 0, 0);
			ResetVelocity();
		}
		else{
			mCoinNode->setPosition(0,100,0);
			velocity1 *= 0;
		}
	}
	if(pos2.x < -50){
		p1Score++;
		if(velocity1.x == 0){
			mCoinNode->setPosition(-30,0,0);
			mCoinNode2->setPosition(30, 0, 0);
			ResetVelocity();
		}
		else{
			mCoinNode2->setPosition(0,100,0);
			velocity2 *= 0;
		}
	}
	if(pos2.x > 50){
		p2Score++;
		if(velocity1.x == 0){
			mCoinNode->setPosition(-30,0,0);
			mCoinNode2->setPosition(30, 0, 0);
			ResetVelocity();
		}
		else{
			mCoinNode2->setPosition(0,100,0);
			velocity2 *= 0;
		}
	}



	if(coinEnt->getWorldBoundingBox().intersects(NPaddleEnt->getWorldBoundingBox())){
		velocity1.x *= -2;
		int i = 0;
		while(i<=5){
			mCoinNode->translate(velocity1*time);
			i++;
		}
	}
	if(coinEnt2->getWorldBoundingBox.   getWorldBoundingBox().intersects(NPaddleEnt->getWorldBoundingBox())){
		velocity2.x *= -2;
		int i = 0;
		while(i<=5){
			mCoinNode2->translate(velocity2*time);
			i++;
		}
	}


	if(coinEnt->getWorldBoundingBox().intersects(RPaddleEnt->getWorldBoundingBox())){
		velocity1.x *= -1;
		int i = 0;
		while(i<=5){
			mCoinNode->translate(velocity1*time);
			i++;
		}
	}
	if(coinEnt2->getWorldBoundingBox().intersects(RPaddleEnt->getWorldBoundingBox())){
		velocity2.x *= -1;
		int i = 0;
		while(i<=5){
			mCoinNode2->translate(velocity2*time);
			i++;
		}
	}

	if(coinEnt->getWorldBoundingBox().intersects(LPaddleEnt->getWorldBoundingBox())){
		velocity1.x *= -1;
		int i = 0;
		while(i<=5){
			mCoinNode->translate(velocity1*time);
			i++;
		}
	}
	if(coinEnt2->getWorldBoundingBox().intersects(LPaddleEnt->getWorldBoundingBox())){
		velocity2.x *= -1;
		int i = 0;
		while(i<=5){
			mCoinNode2->translate(velocity2*time);
			i++;
		}
	}

	// We can move the single object around using the input manager ...

	 if (mInputHandler->IsKeyDown(OIS::KC_UP))
	 {
		 mLeftPaddle->translate(0, time * CoinSpeed, 0);

	 }
	 else if (mInputHandler->IsKeyDown(OIS::KC_DOWN))
	 {
		 mLeftPaddle->translate(0, -time * CoinSpeed, 0);
	 }

	 
	 if(pos.x < 0){
		// if(padPos.y > -40 && padPos.y < 40){
		 mRightPaddle->setPosition(padPos.x, pos.y, 0 );
		 //}
	 }
	 if(pos2.x < 0){
		// if(padPos.y > -40 && padPos.y < 40){
		 mRightPaddle->setPosition(padPos.x, pos2.y, 0 );
		 //}
	 }


	 // Some other fun stuff to try:
	 //mCoinNode->yaw(Ogre::Radian(time * RADIANS_PER_SECOND));
	 //mCoinNode->roll(Ogre::Radian(time * RADIANS_PER_SECOND));

	 Ogre::String pScore = Ogre::StringConverter::toString(p1Score);
	 Ogre::String AIScore = Ogre::StringConverter::toString(p2Score);

	 Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	 Ogre::TextAreaOverlayElement *te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("Sample/Panel/Text1");
	 te->setCaption("Player 1: " + pScore + "\t\t\t\t\t\t\t\t\t\t\t\tPlayer 2: " + AIScore);
	 //te->show();
}


