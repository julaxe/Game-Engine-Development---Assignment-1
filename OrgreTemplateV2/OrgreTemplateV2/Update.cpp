#include "Update.h"
#include "Boundaries.h"
#include "Game.h"
#include <iostream>

enum CollisionPlanes
{
    Y_COLLISION = 0,
    X_COLLISION = 1,
    NO_COLLISION = 2
};
Update::Update()
{
    m_pNode = Game::g_pRoot->getSceneManager("SceneManager")->createSceneNode("Update");
}

bool Update::frameStarted(const FrameEvent& evt)
{
    m_pPlayerRef->Update(evt);
    for(auto gameObject : m_gameObjectsList)
    {
        
        if(gameObject->GetTag() == GameObjectTag::Boundary)
        {
            Boundaries * boundaries = static_cast<Boundaries*>(gameObject);
            if(m_pPlayerRef->CheckForCollision(boundaries->GetLeftWall()))
            {
                std::cout<< "Left wall collision" << std::endl;
            }
            else if(m_pPlayerRef->CheckForCollision(boundaries->GetRightWall()))
            {
                std::cout<< "Right wall collision" << std::endl;
            }
            else if(m_pPlayerRef->CheckForCollision(boundaries->GetBackWall()))
            {
                std::cout<< "Back wall collision" << std::endl;
            }
            else if(m_pPlayerRef->CheckForCollision(boundaries->GetLavaWall()))
            {
                //reset life
            }
            
            //update the boundaries position when player is moving up
            if(m_pPlayerRef->GetVelocity().y > 0)
            {
                gameObject->Update(evt);
            }
        }
        else
        {
            gameObject->Update(evt);
        }
        if(gameObject->GetTag() == GameObjectTag::Platform)
        {
            if(m_pPlayerRef->GetVelocity().y > 0)
            {
                continue;
            }
            if(m_pPlayerRef->CheckForCollision(gameObject))
            {
                if(m_pPlayerRef->GetNode()->getPosition().y < gameObject->GetNode()->getPosition().y)
                {
                    continue;
                }
                Ogre::Vector3 newPosition = Ogre::Vector3(m_pPlayerRef->GetNode()->getPosition().x, gameObject->GetNode()->getPosition().y + gameObject->GetHeight() * 0.5f + m_pPlayerRef->GetRadius() + 1, m_pPlayerRef->GetNode()->getPosition().z);
                m_pPlayerRef->GetNode()->setPosition(newPosition);
                m_pPlayerRef->Bounce(X_COLLISION);
            }
            
            
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
