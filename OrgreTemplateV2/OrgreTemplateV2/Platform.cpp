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
	m_pEntity->setCastShadows(false);
	m_pEntity->setMaterial(Ogre::MaterialManager::getSingleton().getByName("MyMaterial2"));
	m_pNode = Game::g_pRoot->getSceneManager("SceneManager")->createSceneNode("Platform " + s_iId);
	m_pNode->attachObject(m_pEntity);
	//m_pNode->showBoundingBox(true);
	m_pNode->setPosition(Ogre::Vector3(0.0f, 0.0f, 0.0f));
	m_pNode->setScale(2.f, 0.4f, 2.0f);

	m_fWidth = m_pEntity->getBoundingBox().getSize().x * m_pNode->getScale().x;
	m_fHeight = m_pEntity->getBoundingBox().getSize().y * m_pNode->getScale().y;
	m_fLength = m_pEntity->getBoundingBox().getSize().z * m_pNode->getScale().z;

	SetTag(GameObjectTag::Platform);
	s_iId++;
}

void Platform::Update(const FrameEvent& evt)
{
	GameObject::Update(evt);
	float distanceToPlayer = Game::Instance()->GetPlayer()->GetNode()->getPosition().y - GetNode()->getPosition().y;

	if(distanceToPlayer > 500)
	{
		Game::Instance()->GetPlatformsPool()->ThrowBackObjectToPool(this);
		Game::Instance()->GenerateNewPlatform();
	}
}



