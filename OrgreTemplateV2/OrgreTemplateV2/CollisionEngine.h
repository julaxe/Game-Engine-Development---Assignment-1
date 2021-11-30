#pragma once
#include "GameObject.h"
#include "Player.h"

static class CollisionEngine
{
public:
    static void CheckCollision(Player* player, GameObject* object);
};
