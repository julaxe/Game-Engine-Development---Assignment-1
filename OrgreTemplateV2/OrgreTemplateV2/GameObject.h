#pragma once
#include "Ogre.h"

using namespace Ogre;
enum class GameObjectTag
{
    Default,
    Platform,
    Player
};
class GameObject
{
public:
    GameObject();
    virtual void Update(const FrameEvent& evt);
    void SetTag(GameObjectTag newTag);
    GameObjectTag GetTag();
    float GetHeight();
    float GetWidth();
    Ogre::Vector3 GetPosition();
    void SetPosition(Ogre::Vector3 newPosition);
    SceneNode* GetNode();

protected:
    GameObjectTag m_tag;
    SceneNode* m_pNode;
    Entity* m_pEntity;

    float m_fHeight;
    float m_fWidth;
};
