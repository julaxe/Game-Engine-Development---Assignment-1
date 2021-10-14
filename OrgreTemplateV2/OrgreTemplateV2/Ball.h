#pragma once
#include "Paddle.h"

//============ BALL CLASS ====================

enum CollisionPlanes;
class Ball : public Ogre::FrameListener
{
public:
	Ball(Ogre::SceneManager* sceneManager, Paddle* paddle);

	SceneNode* GetNode();

private:

	bool frameStarted(const Ogre::FrameEvent& evt) override;
	void Bounce(enum CollisionPlanes collisionPlane);
	bool CheckForCollision();
	bool CheckCollisionWithScreen();
	bool CheckCollisionWithPaddle();
	void ResetBallPos();

private:

	SceneNode* m_pNode;
	Entity* m_pEntity;

	Paddle* m_pPaddle;

	Ogre::Vector3 m_vInit_Pos;
	Ogre::Vector3 m_vMoveDirection;

	float m_fRadius;
	float m_fMoveSpeed;

};