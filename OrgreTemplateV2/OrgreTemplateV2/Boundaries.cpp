#include "Boundaries.h"

#include "Game.h"

Boundaries::Boundaries(GameObject* playerRef)
{
    m_playerRef = playerRef;
    //m_pEntity = Game::g_pRoot->getSceneManager("SceneManager")->createEntity("cube.mesh");
    m_pNode = Game::g_pRoot->getSceneManager("SceneManager")->createSceneNode("Boundaries");
    SetTag(GameObjectTag::Boundary);
    
    GameObject* leftWall = new GameObject(m_pNode);
    GameObject* rightWall = new GameObject(m_pNode);
    GameObject* backWall = new GameObject(m_pNode);
    //GameObject* frontWall = new GameObject(m_pNode);
    GameObject* lavaWall = new GameObject(m_pNode);

    leftWall->GetNode()->attachObject(Game::g_pRoot->getSceneManager("SceneManager")->createEntity("cube.mesh"));
    rightWall->GetNode()->attachObject(Game::g_pRoot->getSceneManager("SceneManager")->createEntity("cube.mesh"));
    backWall->GetNode()->attachObject(Game::g_pRoot->getSceneManager("SceneManager")->createEntity("cube.mesh"));
    //Ogre::Entity* frontWallEntity = Game::g_pRoot->getSceneManager("SceneManager")->createEntity("cube.mesh");
    //frontWall->GetNode()->attachObject(m_pEntity);
    lavaWall->GetNode()->attachObject(Game::g_pRoot->getSceneManager("SceneManager")->createEntity("cube.mesh"));
    
    float height = 20.f;
    float width = 20.f;
    float thightness = 0.4f;
    float scale = 100.0f;
    leftWall->GetNode()->setScale(thightness, height, width);
    rightWall->GetNode()->setScale(thightness, height, width);
    backWall->GetNode()->setScale(width, height, thightness);
    //frontWall->GetNode()->setScale(20.f, 20.f, 0.4f);
    lavaWall->GetNode()->setScale(width, thightness, width);

    
    //set positions
    float lavaPosition = 10.f;
    leftWall->GetNode()->setPosition(Ogre::Vector3(-0.5f*scale*width, 0.0f, 0.0f));
    rightWall->GetNode()->setPosition(Ogre::Vector3(0.5f*scale*width, 0.0f, 0.0f));
    backWall->GetNode()->setPosition(Ogre::Vector3(0.0f, 0.0f, -0.5f*scale*width));
    //frontWall->GetNode()->setPosition(Ogre::Vector3(0.0f, 0.0f, 0.5f*width));
    lavaWall->GetNode()->setPosition(Ogre::Vector3(0.0f, -lavaPosition*scale, 0.0f));
    
}

void Boundaries::Update(const FrameEvent& evt)
{
    GameObject::Update(evt);
    GetNode()->setPosition(Vector3(0.0f,m_playerRef->GetNode()->getPosition().y, 0.0f));
}
