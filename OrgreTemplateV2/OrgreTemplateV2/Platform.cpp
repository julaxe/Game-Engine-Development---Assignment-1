#include "Platform.h"
#include "Game.h"
#include <iostream>
/// <summary>
/// Contructor for the Platform.
/// Creates a mesh and a Node, then attach it to the Scene Manager.
/// Set the initial values for our Platform.
/// </summary>
int Platform::s_iId = 0;
Platform::Platform()
{
	m_pEntity = Game::g_pRoot->getSceneManager("SceneManager")->createEntity("cube.mesh");
	m_pNode = Game::g_pRoot->getSceneManager("SceneManager")->createSceneNode("Platform " + s_iId);
	m_pNode->attachObject(m_pEntity);
	m_pNode->setPosition(Ogre::Vector3(0.0f, 0.0f, 0.0f));
	m_pNode->setScale(2.f, 0.4f, 2.0f);

	m_fWidth = m_pEntity->getBoundingBox().getSize().x * m_pNode->getScale().x;
	m_fHeight = m_pEntity->getBoundingBox().getSize().y * m_pNode->getScale().y;

	SetTag(GameObjectTag::Platform);
	s_iId++;
}



