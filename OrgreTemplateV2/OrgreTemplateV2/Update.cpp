#include "Update.h"
#include "Game.h"

Update::Update()
{
    m_pNode = Game::g_pRoot->getSceneManager("SceneManager")->createSceneNode("Update");
}

bool Update::frameStarted(const FrameEvent& evt)
{
    m_pPlayerRef->Update(evt);
    for(auto gameObject : m_gameObjectsList)
    {
        gameObject->Update(evt);
        if(gameObject->GetTag() == GameObjectTag::Platform)
        {
            m_pPlayerRef->CheckForCollision(gameObject);
        }
    }
    

    //Call collision manager.
    return true;
}

bool Update::frameEnded(const FrameEvent& evt)
{
    return true;
}

void Update::addGameObject(GameObject* gameObject)
{
    m_gameObjectsList.push_back(gameObject);
}

void Update::SetPlayerRef(Player* player)
{
    m_pPlayerRef = player;
}

SceneNode* Update::GetNode()
{
    return m_pNode;
}
