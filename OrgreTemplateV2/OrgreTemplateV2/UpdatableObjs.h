#pragma once
#include "Ogre.h"
#include "OgreTrays.h"

using namespace Ogre;

//============ PADDLE CLASS ====================

class Paddle : public Ogre::FrameListener
{
public:

	Paddle(Ogre::SceneManager* sceneManager);
	
	bool frameStarted(const Ogre::FrameEvent& evt);
	

	SceneNode* GetNode();

	void SetMoveDirection(Ogre::Vector3 direction);

	int GetLives();
	int GetScore();

	
private:
	
	//Ogre::ManualObject* _manualObjPaddle;

	SceneNode* _node;
	Entity* _entity;
	float moveSpeed;
	Ogre::Vector3 moveDirection;

	int lives;
	int score;
};

//============ BALL CLASS ====================



//============ LABEL CLASS ====================
class UILabels : public Ogre::FrameListener 
{
public:

	UILabels(Ogre::RenderWindow* rendererWindow, Paddle* paddle);

	Paddle* paddleTest;

	bool frameStarted(const Ogre::FrameEvent& evt);

	OgreBites::TrayManager* GetTrayManager();

	void RefreshUI(int lives, int score);

private:

	OgreBites::TrayManager* _mTrayManager;

	StringVector _paramNames;


	//this works but I`m not a fan of the counter
	OgreBites::Label* _timerText;
	OgreBites::Label* _time;
	Timer timer;
	int counter;

	OgreBites::ParamsPanel* _panel;
};