#pragma once
#include "Ogre.h"

using namespace Ogre;


class Paddle : public Ogre::FrameListener
{
public:

	Paddle(Ogre::SceneManager* sceneManager);
	
	bool frameStarted(const Ogre::FrameEvent& evt);
	
	SceneNode* GetNode();

	Ogre::Vector3 translate;
	
private:
	SceneNode* _node;
	Entity* _entity;
	float MoveSpeed;
};

