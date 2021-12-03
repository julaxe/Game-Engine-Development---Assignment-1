#pragma once
#include "Ogre.h"

using namespace Ogre;
enum class GameObjectTag
{
    Default,
    Platform,
    Player,
    Boundary,
    Camera
};
class GameObject
{
public:
    GameObject();
    GameObject(bool withNode);
    GameObject(SceneNode* parentNode);
    virtual void Update(const FrameEvent& evt);
    void SetTag(GameObjectTag newTag);
    void UpdateDimensions();
    GameObjectTag GetTag();
    float GetHeight();
    float GetWidth();
    float GetLength();
    Ogre::Vector3 GetPosition();
    void SetPosition(Ogre::Vector3 newPosition);
    SceneNode* GetNode();

protected:
    GameObjectTag m_tag;
    SceneNode* m_pNode;
    Entity* m_pEntity;

    float m_fHeight;
    float m_fWidth;
    float m_fLength;
};
