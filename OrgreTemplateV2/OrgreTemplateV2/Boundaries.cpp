#include "Boundaries.h"

#include "Game.h"

Boundaries::Boundaries(GameObject* playerRef)
{
    m_playerRef = playerRef;
    //m_pEntity = Game::g_pRoot->getSceneManager("SceneManager")->createEntity("cube.mesh");
    m_pNode = Game::g_pRoot->getSceneManager("SceneManager")->createSceneNode("Boundaries");
    SetTag(GameObjectTag::Boundary);
    
    CreatePointLight();
    CreateBoundaries();
}

void Boundaries::Update(const FrameEvent& evt)
{
    GameObject::Update(evt);
    GetNode()->setPosition(Vector3(0.0f,m_playerRef->GetNode()->getPosition().y, 0.0f));
}

GameObject* Boundaries::GetLeftWall()
{
    return m_pLeftWall;
}

GameObject* Boundaries::GetRightWall()
{
    return m_pRightWall;
}

GameObject* Boundaries::GetBackWall()
{
    return m_pBackWall;
}

GameObject* Boundaries::GetForwardWall()
{
    return m_pForwardWall;
}

GameObject* Boundaries::GetLavaWall()
{
    return m_pLavaWall;
}

void Boundaries::CreatePointLight()
{
    Light* pointLight = Game::g_pRoot->getSceneManager("SceneManager")->createLight("pointLight");
    pointLight->setDiffuseColour(1,1,1);
    pointLight->setSpecularColour(1,1,1);
    pointLight->setPowerScale(1.0);
    pointLight->setType(Light::LT_POINT);

    SceneNode* pointLightNode = GetNode()->createChildSceneNode();
    pointLightNode->attachObject(pointLight);
    pointLightNode->setPosition(0,2000,0);
}

void Boundaries::CreateBoundaries()
{
    m_pLeftWall = new GameObject(m_pNode);
    m_pRightWall = new GameObject(m_pNode);
    m_pBackWall = new GameObject(m_pNode);
    //GameObject* frontWall = new GameObject(m_pNode);
    m_pLavaWall= new GameObject(m_pNode);
    
    m_pLeftWall->GetNode()->attachObject(Game::g_pRoot->getSceneManager("SceneManager")->createEntity("cube.mesh"));
    m_pRightWall->GetNode()->attachObject(Game::g_pRoot->getSceneManager("SceneManager")->createEntity("cube.mesh"));
    m_pBackWall->GetNode()->attachObject(Game::g_pRoot->getSceneManager("SceneManager")->createEntity("cube.mesh"));
    //Ogre::Entity* frontWallEntity = Game::g_pRoot->getSceneManager("SceneManager")->createEntity("cube.mesh");
    //frontWall->GetNode()->attachObject(m_pEntity);
    m_pLavaWall->GetNode()->attachObject(Game::g_pRoot->getSceneManager("SceneManager")->createEntity("cube.mesh"));
    
    float height = 20.f;
    float width = 10.f;
    float thightness = 0.4f;
    float scale = 100.0f;

    m_pLeftWall->GetNode()->setScale(thightness, height, width);
    m_pRightWall->GetNode()->setScale(thightness, height, width);
    m_pBackWall->GetNode()->setScale(width, height, thightness);
    //frontWall->GetNode()->setScale(20.f, 20.f, 0.4f);
    m_pLavaWall->GetNode()->setScale(width, thightness, width);
    
    m_pLeftWall->UpdateDimensions();
    m_pRightWall->UpdateDimensions();
    m_pBackWall->UpdateDimensions();
    //frontWall->UpdateDimensions();
    m_pLavaWall->UpdateDimensions();
    
    
    //set positions
    float lavaPosition = 10.f;
    m_pLeftWall->GetNode()->setPosition(Ogre::Vector3(-0.5f*scale*width, 0.0f, 0.0f));
    m_pRightWall->GetNode()->setPosition(Ogre::Vector3(0.5f*scale*width, 0.0f, 0.0f));
    m_pBackWall->GetNode()->setPosition(Ogre::Vector3(0.0f, 0.0f, -0.5f*scale*width));
    //frontWall->GetNode()->setPosition(Ogre::Vector3(0.0f, 0.0f, 0.5f*width));
    m_pLavaWall->GetNode()->setPosition(Ogre::Vector3(0.0f, -lavaPosition*scale, 0.0f));
}
