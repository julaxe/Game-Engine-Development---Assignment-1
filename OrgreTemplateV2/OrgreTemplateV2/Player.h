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
	void CheckForCollision(GameObject* gameObject);

private:
	void Bounce(enum CollisionPlanes collisionPlane);
	bool CheckCollisionWithScreen();
	bool CheckCollisionWithGameObject(GameObject* object);
	void ResetBallPos();

private:

	
	Ogre::Vector3 m_oldPosition;

	Ogre::Vector3 m_vInit_Pos;
	Ogre::Vector3 m_vMoveDirection;

	float m_fRadius;
	float m_fMoveSpeed;

};