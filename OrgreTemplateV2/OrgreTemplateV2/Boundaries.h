#pragma once
#include "GameObject.h"

class Boundaries : public GameObject
{
public:
    Boundaries(GameObject* playerRef);
    void Update(const FrameEvent& evt) override;
    GameObject* GetLeftWall();
    GameObject* GetRightWall();
    GameObject* GetBackWall();
    GameObject* GetForwardWall();
    GameObject* GetLavaWall();

private:
    void CreatePointLight();
    void CreateBoundaries();
private:
    GameObject* m_playerRef;

    GameObject* m_pLeftWall;
    GameObject* m_pRightWall;
    GameObject* m_pBackWall;
    GameObject* m_pForwardWall;
    GameObject* m_pLavaWall;
    
};
