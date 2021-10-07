
#include "Paddle.h"

Paddle::Paddle(Ogre::SceneManager* sceneManager)
{

	_node = sceneManager->createSceneNode("Paddle");
	_entity = sceneManager->createEntity("cube.mesh");
	_node->attachObject(_entity);
	_node->setPosition(Ogre::Vector3(0.0f, -300.f, 0.0f));
	_node->setScale(2.f, 0.4f, 0.4f);
	MoveSpeed = 500;
}

bool Paddle::frameStarted(const Ogre::FrameEvent& evt)
{
	_node->translate(translate * MoveSpeed * evt.timeSinceLastFrame);
	translate = translate * 0.98;
	return true;
}

SceneNode* Paddle::GetNode() {
	return _node;
}