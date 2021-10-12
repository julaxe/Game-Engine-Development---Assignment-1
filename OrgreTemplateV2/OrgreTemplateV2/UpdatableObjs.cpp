
#include "UpdatableObjs.h"
#include <iostream>

Paddle::Paddle(Ogre::SceneManager* sceneManager)
{

	_entity = sceneManager->createEntity("cube.mesh");
	_node = sceneManager->createSceneNode("PaddleNode");
	_node->attachObject(_entity);
	_node->setPosition(Ogre::Vector3(0.0f, -300.0f, 0.0f));
	_node->setScale(2.f, 0.4f, 0.4f);

	width = _entity->getBoundingBox().getSize().x * _node->getScale().x;
	height = _entity->getBoundingBox().getSize().y * _node->getScale().y;
	std::cout << width << "," << height << std::endl;
	moveSpeed = 500;
	lives = 5;
	score = 0;
}

bool Paddle::frameStarted(const Ogre::FrameEvent& evt)
{
	float const screenWidth = 560;
	_node->translate(moveDirection * moveSpeed * evt.timeSinceLastFrame);
	if (_node->getPosition().x > screenWidth || _node->getPosition().x < -screenWidth)
	{
		_node->translate(-moveDirection * moveSpeed * evt.timeSinceLastFrame);
	}
	moveDirection = moveDirection * 0.98;
	return true;
}

SceneNode* Paddle::GetNode() 
{
	return _node;
}

void Paddle::SetMoveDirection(Ogre::Vector3 direction)
{
	moveDirection = direction;
}

int Paddle::GetLives()
{
	return lives;
}

void Paddle::SetLives(int lives)
{
	this->lives = lives;
}

int Paddle::GetScore()
{
	return score;
}

float Paddle::GetHeight()
{
	return height;
}

float Paddle::GetWidth()
{
	return width;
}


//============ BALL CLASS ====================


Ball::Ball(Ogre::SceneManager* sceneManager, Paddle* paddle)
{
	_entity = sceneManager->createEntity("sphere.mesh");
	_node = sceneManager->createSceneNode("BallNode");
	_paddle = paddle;
	_node->attachObject(_entity);
	_node->setPosition(Ogre::Vector3(0.0f, 300.0f, 0.0f));
	_node->setScale(0.3f, 0.3f, 0.3f);

	//initial values
	//go up first - diagonal
	radius = _entity->getBoundingBox().getSize().x * _node->getScale().x * 0.5f;
	moveDirection = Ogre::Vector3(1.0f, 1.0f, 0.0f);
	moveSpeed = 200.0f;

}

SceneNode* Ball::GetNode()
{
	return _node;
}

bool Ball::frameStarted(const Ogre::FrameEvent& evt)
{
	_node->translate(moveDirection * moveSpeed * evt.timeSinceLastFrame);
	if (checkCollision())
	{
		
	}
	return true;
}

void Ball::bounce(bool isSideCollision)
{
	if (isSideCollision)
	{
		moveDirection.x = -moveDirection.x;
	}
	else
	{
		moveDirection.y = -moveDirection.y;
	}
}

bool Ball::checkCollision()
{
	//collision with the borders
	float const screenWidth = 630;
	float const screenHeight = 470;
	if (_node->getPosition().x > screenWidth || _node->getPosition().x < -screenWidth)
	{
		bounce(true);
		return true;
	}
	if (_node->getPosition().y > screenHeight || _node->getPosition().y < -screenHeight)
	{
		bounce(false);
		return true;
	}
	//collision with Paddle.
	if (checkCollisionWithPaddle())
	{
		bounce(false);
		return true;
	}

	return false;
}

bool Ball::checkCollisionWithPaddle()
{
	//get center point circle first
	Ogre::Vector3 center = _node->getPosition();

	//calculate AABB info (center, half-extents);
	Ogre::Vector3 aabb_half_entents = Ogre::Vector3(_paddle->GetWidth(), _paddle->GetHeight(), 0.0f) * 0.5;
	Ogre::Vector3 aabb_center = _paddle->GetNode()->getPosition();

	//get difference vectro beween both centers;
	Ogre::Vector3 difference = center - aabb_center;
	Ogre::Vector3 clamped = Ogre::Vector3(Ogre::Math::Clamp<Real>(difference.x, -aabb_half_entents.x, aabb_half_entents.x), 
		Ogre::Math::Clamp<Real>(difference.y, -aabb_half_entents.y, aabb_half_entents.y), 0.0f);

	//add value to aabb center and we get the value of box closest to circle
	Ogre::Vector3 closest = aabb_center + clamped;
	//retrieve vector between center circle and closest point AABB and check if lenght <= radius
	difference = closest - center;

	if (difference.length() < radius)
	{
		return true;
	}

	return false;
}

//============ LABEL CLASS ====================

UILabels::UILabels(Ogre::RenderWindow* rendererWindow, Paddle* paddle)
{
	_mTrayManager = new OgreBites::TrayManager("Title", rendererWindow);

	//set up of UI preferences
	_mTrayManager->showFrameStats(OgreBites::TL_BOTTOMRIGHT);
	_mTrayManager->toggleAdvancedFrameStats();
	//_mTrayManager->hideCursor();

	paddleTest = paddle;

	timer = Ogre::Timer();
	counter = 0;
	_timerText = _mTrayManager->createLabel(OgreBites::TL_TOP, "timerText", "TIMER", 100);
	_time = _mTrayManager->createLabel(OgreBites::TL_TOP, "time", " ", 100);


	//Populating array of strings to display
	_paramNames.push_back("Score");
	_paramNames.push_back("Lives");

	_panel = _mTrayManager->createParamsPanel(OgreBites::TL_TOPLEFT, "ScoreBoard", 150, _paramNames);

}

bool UILabels::frameStarted(const Ogre::FrameEvent& evt)
{

	if ((counter % 60) == 0)
	{
		_time->setCaption(Ogre::StringConverter().toString(timer.getMilliseconds() / 1000));
		counter = 0;
	}
	_panel->setParamValue(0, Ogre::StringConverter::toString(paddleTest->GetScore()));
	_panel->setParamValue(1, Ogre::StringConverter::toString(paddleTest->GetLives()));
	

	counter++;

	return true;
}

OgreBites::TrayManager* UILabels::GetTrayManager()
{
	return _mTrayManager;
}

void UILabels::RefreshUI(int lives, int score)
{
	
}

