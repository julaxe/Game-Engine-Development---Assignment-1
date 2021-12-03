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
                //player on the right wall
                Vector3 rightwallPosition = boundaries->GetRightWall()->GetNode()->_getDerivedPosition();
                Vector3 leftSideOfRightWall = Vector3(rightwallPosition.x - 100.0f, m_pPlayerRef->GetNode()->getPosition().y, m_pPlayerRef->GetNode()->getPosition().z);
                m_pPlayerRef->GetNode()->setPosition(leftSideOfRightWall);
            }
            else if(m_pPlayerRef->CheckForCollision(boundaries->GetRightWall()))
            {
                Vector3 leftWallPosition = boundaries->GetLeftWall()->GetNode()->_getDerivedPosition();
                Vector3 rightSideOfLeftWall = Vector3(leftWallPosition.x + 100.0f, m_pPlayerRef->GetNode()->getPosition().y, m_pPlayerRef->GetNode()->getPosition().z);
                m_pPlayerRef->GetNode()->setPosition(rightSideOfLeftWall);
            }
            else if(m_pPlayerRef->CheckForCollision(boundaries->GetBackWall()))
            {
                Vector3 backWallPosition = boundaries->GetBackWall()->GetNode()->_getDerivedPosition();
                Vector3 frontSideOfBackWall = Vector3(m_pPlayerRef->GetNode()->getPosition().x, m_pPlayerRef->GetNode()->getPosition().y, backWallPosition.z+1000);
                m_pPlayerRef->GetNode()->setPosition(frontSideOfBackWall);

            }
            else if(m_pPlayerRef->CheckForCollision(boundaries->GetLavaWall()))
            {
                m_pPlayerRef->ResetPositionToBottomPlatform();
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
