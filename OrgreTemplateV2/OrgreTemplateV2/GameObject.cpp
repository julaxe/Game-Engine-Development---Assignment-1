#include "GameObject.h"

GameObject::GameObject()
{
    m_tag = GameObjectTag::Default;
}

void GameObject::Update(const FrameEvent& evt)
{
}

void GameObject::SetTag(GameObjectTag newTag)
{
    m_tag = newTag;
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
