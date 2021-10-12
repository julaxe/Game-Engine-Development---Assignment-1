#pragma once
#include "Ogre.h"
#include "OgreTrays.h"

using namespace Ogre;

//============ PADDLE CLASS ====================

class Paddle : public Ogre::FrameListener
{
public:

	Paddle(Ogre::SceneManager* sceneManager);
	
	

	SceneNode* GetNode();

	void SetMoveDirection(Ogre::Vector3 direction);

	int GetLives();
	void SetLives(int lives);
	int GetScore();

	float GetHeight();
	float GetWidth();

	
private:
	
	bool frameStarted(const Ogre::FrameEvent& evt);

	SceneNode* _node;
	Entity* _entity;

	float width;
	float height;

	float moveSpeed;
	Ogre::Vector3 moveDirection;

	int lives;
	int score;
};

//============ BALL CLASS ====================

class Ball : public Ogre::FrameListener
{
public:

	Ball(Ogre::SceneManager* sceneManager, Paddle* paddle);

	SceneNode* GetNode();


private:

	bool frameStarted(const Ogre::FrameEvent& evt);
	void bounce(bool isSideCollision);
	bool checkCollision();
	bool checkCollisionWithPaddle();

	SceneNode* _node;
	Entity* _entity;
	Paddle* _paddle;


	float radius;

	float moveSpeed;
	Ogre::Vector3 moveDirection;

};

//============ LABEL CLASS ====================
class UILabels : public Ogre::FrameListener 
{
public:

	UILabels(Ogre::RenderWindow* rendererWindow, Paddle* paddle);


	bool frameStarted(const Ogre::FrameEvent& evt);

	OgreBites::TrayManager* GetTrayManager();

	void RefreshUI(int lives, int score);

private:
	Paddle* paddleTest;

	OgreBites::TrayManager* _mTrayManager;

	StringVector _paramNames;


	//this works but I`m not a fan of the counter
	OgreBites::Label* _timerText;
	OgreBites::Label* _time;
	Timer timer;
	int counter;

	OgreBites::ParamsPanel* _panel;
};