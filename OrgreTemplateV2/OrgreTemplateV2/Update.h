#pragma once
#include "Ogre.h"
#include "GameObject.h"
#include <vector>

#include "Player.h"
using namespace Ogre;

class Update : public FrameListener
{
public:
    Update();
    bool frameStarted(const FrameEvent& evt) override;
    bool frameEnded(const FrameEvent& evt) override;
    void addGameObject(GameObject* gameObject);
    void SetPlayerRef(Player* player);
    SceneNode* GetNode();
private:
    SceneNode* m_pNode;
    Player* m_pPlayerRef;
    std::vector<GameObject*> m_gameObjectsList;
};
