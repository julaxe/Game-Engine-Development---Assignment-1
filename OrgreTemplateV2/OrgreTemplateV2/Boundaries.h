#pragma once
#include "GameObject.h"

class Boundaries : public GameObject
{
public:
    Boundaries(GameObject* playerRef);
    void Update(const FrameEvent& evt) override;

private:
    GameObject* m_playerRef;
};
