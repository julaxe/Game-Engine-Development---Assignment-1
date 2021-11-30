#include "Ball.h"
#include <iostream>
//============ BALL CLASS ====================
/// <summary>
/// Planes where the elements in the game can collide with.
/// </summary>
enum CollisionPlanes
{
	Y_COLLISION = 0,
	X_COLLISION = 1,
	NO_COLLISION = 2
};
/// <summary>
/// Constructor of the Ball.
/// Set the node and the mesh for the Ball.
/// Set the initial values for the ball (speed and direction).
/// </summary>
/// <param name="sceneManager"></param>
/// <param name="paddle"></param>
Ball::Ball(Ogre::SceneManager* sceneManager)
{
	m_vInit_Pos = Ogre::Vector3(0.0f, 300.0f, 0.0f);
	m_pEntity = sceneManager->createEntity("sphere.mesh");
	m_pNode = sceneManager->createSceneNode("BallNode");

	m_pNode->attachObject(m_pEntity);
	m_pNode->setPosition(m_vInit_Pos);
	m_pNode->setScale(0.3f, 0.3f, 0.3f);

	//initial values
	//go up first - diagonal
	m_fRadius = m_pEntity->getBoundingBox().getSize().x * m_pNode->getScale().x * 0.5f;
	m_vMoveDirection = Ogre::Vector3(1.0f, 1.0f, 0.0f);
	m_fMoveSpeed = 400.0f;

}
/// <summary>
/// Returns the node of the ball.
/// </summary>
/// <returns></returns>
SceneNode* Ball::GetNode()
{
	return m_pNode;
}
/// <summary>
/// Function called at the start of every frame.
/// Move the ball in a set direction with a set speed.
/// It check for collision every frame and bounce if it's true.
/// </summary>
/// <param name="evt"></param>
/// <returns></returns>
bool Ball::frameStarted(const Ogre::FrameEvent& evt)
{
	Ogre::Vector3 oldPosition = m_pNode->getPosition();
	m_pNode->translate(m_vMoveDirection * m_fMoveSpeed * evt.timeSinceLastFrame);
	if (CheckForCollision())
	{
		m_pNode->setPosition(oldPosition);
	}

	return true;
}
/// <summary>
/// Function called every time the ball collides.
/// Change the direction of the ball depending with which plane collides.
/// </summary>
/// <param name="collisionPlane"></param>
void Ball::Bounce(CollisionPlanes collisionPlane)
{
	switch (collisionPlane)
	{
	case Y_COLLISION:
		m_vMoveDirection.x = -m_vMoveDirection.x;
		//update the position
		// Add to score 
		
		break;
	case X_COLLISION:
		m_vMoveDirection.y = -m_vMoveDirection.y;
		// Add to score 
		break;
	case NO_COLLISION:
		break;
	default:
		break;
	}
}
/// <summary>
/// Check for collision with the screen or the paddle.
/// </summary>
/// <returns></returns>
bool Ball::CheckForCollision()
{
	return CheckCollisionWithPaddle() || CheckCollisionWithScreen();
}

/// <summary>
/// Reset the ball position to the initial position, also resets the direction.
/// Takes off one live.
/// </summary>
void Ball::ResetBallPos()
{
	m_pNode->setPosition(m_vInit_Pos);
	m_vMoveDirection = Ogre::Vector3(1.0f, 1.0f, 0.0f);
}

/// <summary>
/// Check for collsion with the borders of the screen.
/// </summary>
/// <returns></returns>
bool Ball::CheckCollisionWithScreen()
{
	//collision with the borders
	float const screenWidth = 630;
	float const screenHeight = 470;
	if (m_pNode->getPosition().x > screenWidth || m_pNode->getPosition().x < -screenWidth)
	{
		Bounce(Y_COLLISION);
		return true;
	}
	if (m_pNode->getPosition().y > screenHeight)
	{
		Bounce(X_COLLISION);
		return true;
	}
	else if (m_pNode->getPosition().y < -screenHeight)
	{
		Bounce(X_COLLISION);
		ResetBallPos();
	}
	return false;
}
/// <summary>
/// Check for collision with the paddle, AABB with circle collision.
/// </summary>
/// <returns></returns>
bool Ball::CheckCollisionWithPaddle()
{
#if DEBUG
	//get center point circle first
	Ogre::Vector3 center = m_pNode->getPosition();

	//calculate AABB info (center, half-extents);
	Ogre::Vector3 aabb_half_entents = Ogre::Vector3(m_pPaddle->GetWidth(), m_pPaddle->GetHeight(), 0.0f) * 0.5;
	Ogre::Vector3 aabb_center = m_pPaddle->GetNode()->getPosition();

	//get difference vectro beween both centers;
	Ogre::Vector3 difference = center - aabb_center;
	Ogre::Vector3 clamped = Ogre::Vector3(Ogre::Math::Clamp<Real>(difference.x, -aabb_half_entents.x, aabb_half_entents.x),
		Ogre::Math::Clamp<Real>(difference.y, -aabb_half_entents.y, aabb_half_entents.y), 0.0f);

	//add value to aabb center and we get the value of box closest to circle
	Ogre::Vector3 closest = aabb_center + clamped;
	//retrieve vector between center circle and closest point AABB and check if lenght <= m_fRadius
	difference = closest - center;

	if (difference.length() < m_fRadius)
	{
		std::cout << "y:" << difference.y << ", x:" << difference.x << std::endl;
		if (Math::Abs(difference.y) >= Math::Abs(difference.x))
		{
			
			//top collision
			//update the position of the ball
			Ogre::Vector3 newPosition = Ogre::Vector3(m_pNode->getPosition().x, m_pPaddle->GetNode()->getPosition().y + m_pPaddle->GetHeight() * 0.5f + m_fRadius + 1, 0.0f);
			m_pNode->setPosition(newPosition);
			Bounce(X_COLLISION);
			//no bottom collision
		}
		else
		{
			if (difference.x >= 0)
			{
				//left side
				Ogre::Vector3 newPosition = Ogre::Vector3(m_pPaddle->GetNode()->getPosition().x - m_pPaddle->GetWidth() * 0.5f - m_fRadius - 1, m_pNode->getPosition().y, 0.0f);
				m_pNode->setPosition(newPosition);
			}
			else
			{
				//right side
				Ogre::Vector3 newPosition = Ogre::Vector3(m_pPaddle->GetNode()->getPosition().x + m_pPaddle->GetWidth() * 0.5f + m_fRadius + 1, m_pNode->getPosition().y, 0.0f);
				m_pNode->setPosition(newPosition);
			}
			Bounce(Y_COLLISION);
		}
		
	}
	return false;
#endif
	return false;
}


