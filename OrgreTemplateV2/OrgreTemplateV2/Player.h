#pragma once
#include <OgreInput.h>
#include "GameObject.h"
#include "Ogre.h"
#include "PhysicsComponent.h"

using namespace Ogre;

//============ BALL CLASS ====================

enum CollisionPlanes;
class Player : public GameObject, public PhysicsComponent
{
public:
	Player();

	void HandleInput(const OgreBites::KeyboardEvent& evt);
	void Update(const FrameEvent& evt) override;
	bool CheckForCollision(GameObject* gameObject);
	float GetRadius();
	void Bounce(enum CollisionPlanes collisionPlane);

	void SetScore(int score);
	int GetScore();
	void SetLifes(int lifes);
	int GetLifes();

	void ResetPositionToBottomPlatform();

private:
	bool CheckCollisionWithScreen();
	bool CheckCollisionWithGameObject(GameObject* object);

private:

	int m_iLifes;
	int m_iScore;
	float m_fRadius;
	float m_fMoveSpeed;

};