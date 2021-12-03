#include "GameObject.h"
#include "Game.h"

GameObject::GameObject()
{
    m_tag = GameObjectTag::Default;
}

GameObject::GameObject(bool withNode)
{
    if (withNode) {
        m_pNode = Game::g_pRoot->getSceneManager("SceneManager")->createSceneNode();
    }
}

GameObject::GameObject(SceneNode* parentNode)
{
    m_pNode =  parentNode->createChildSceneNode();
}

void GameObject::Update(const FrameEvent& evt)
{
}

void GameObject::SetTag(GameObjectTag newTag)
{
    m_tag = newTag;
}

void GameObject::UpdateDimensions()
{
    m_fWidth = m_pNode->getAttachedObject(0)->getBoundingBox().getSize().x * m_pNode->getScale().x;
    m_fHeight = m_pNode->getAttachedObject(0)->getBoundingBox().getSize().y * m_pNode->getScale().y;
    m_fLength = m_pNode->getAttachedObject(0)->getBoundingBox().getSize().z * m_pNode->getScale().z;
}

GameObjectTag GameObject::GetTag()
{
    return m_tag;
}

float GameObject::GetHeight()
{
    return m_fHeight;
}

float GameObject::GetWidth()
{
    return m_fWidth;
}

float GameObject::GetLength()
{
    return m_fLength;
}

Ogre::Vector3 GameObject::GetPosition()
{
    return m_pNode->getPosition();
}

void GameObject::SetPosition(Ogre::Vector3 newPosition)
{
    m_pNode->setPosition(newPosition);
}

SceneNode* GameObject::GetNode()
{
    return m_pNode;
}
