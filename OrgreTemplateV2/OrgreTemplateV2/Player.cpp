#include "Player.h"
#include <iostream>

#include "Game.h"
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
Player::Player()
{
	
	m_vInit_Pos = Ogre::Vector3(0.0f, 300.0f, 0.0f);
	m_pEntity = Game::g_pRoot->getSceneManager("SceneManager")->createEntity("sphere.mesh");
	m_pNode = Game::g_pRoot->getSceneManager("SceneManager")->createSceneNode("BallNode");

	m_pNode->attachObject(m_pEntity);
	m_pNode->setPosition(m_vInit_Pos);
	m_pNode->setScale(0.3f, 0.3f, 0.3f);

	
	//initial values
	//go up first - diagonal
	m_fRadius = m_pEntity->getBoundingBox().getSize().x * m_pNode->getScale().x * 0.5f;
	m_fMoveSpeed = 400.0f;

	//set all the physics variables.
	SetPhysicsComponent(m_pNode);
	c_gravity = 400.0f;
	c_airFriction = 0.01f;
}

void Player::HandleInput(const OgreBites::KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case 'a':
		SetXVelocity(-m_fMoveSpeed);
		break;
	case 'd':
		SetXVelocity(m_fMoveSpeed);
		break;
	default:
		break;
	}
}

/// <summary>
/// Function called at the start of every frame.
/// Move the ball in a set direction with a set speed.
/// It check for collision every frame and bounce if it's true.
/// </summary>
/// <param name="evt"></param>
/// <returns></returns>
void Player::Update(const FrameEvent& evt)
{
	GameObject::Update(evt);
	UpdatePhysics(evt);
}
/// <summary>
/// Function called every time the ball collides.
/// Change the direction of the ball depending with which plane collides.
/// </summary>
/// <param name="collisionPlane"></param>
void Player::Bounce(CollisionPlanes collisionPlane)
{
	switch (collisionPlane)
	{
	case Y_COLLISION:
		m_vMoveDirection.x = -m_vMoveDirection.x;
		//update the position
		// Add to score 
		
		break;
	case X_COLLISION:
		//m_vMoveDirection.y = -m_vMoveDirection.y;
		SetYVelocity(600.0f);
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
void Player::CheckForCollision(GameObject* gameObject)
{
	CheckCollisionWithGameObject(gameObject);
	// if(CheckCollisionWithScreen())
	// {
	// 	m_pNode->setPosition(m_oldPosition);
	// }
}

/// <summary>
/// Reset the ball position to the initial position, also resets the direction.
/// Takes off one live.
/// </summary>
void Player::ResetBallPos()
{
	m_pNode->setPosition(m_vInit_Pos);
	m_vMoveDirection = Ogre::Vector3(1.0f, 1.0f, 0.0f);
}

/// <summary>
/// Check for collsion with the borders of the screen.
/// </summary>
/// <returns></returns>
bool Player::CheckCollisionWithScreen()
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
		//ResetBallPos();
	}
	return false;
}
/// <summary>
/// Check for collision with the paddle, AABB with circle collision.
/// </summary>
/// <returns></returns>
bool Player::CheckCollisionWithGameObject(GameObject* gameObject)
{
	if(GetVelocity().y > 0)
	{
		return false;
	}
	//get center point circle first
	Ogre::Vector3 center = m_pNode->getPosition();

	//calculate AABB info (center, half-extents);
	Ogre::Vector3 aabb_half_entents = Ogre::Vector3(gameObject->GetWidth(), gameObject->GetHeight(), 0.0f) * 0.5;
	Ogre::Vector3 aabb_center = gameObject->GetNode()->getPosition();

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
		if(GetNode()->getPosition().y < gameObject->GetNode()->getPosition().y)
		{
			return false;
		}
		
		if (Math::Abs(difference.y) >= Math::Abs(difference.x))
		{
			
			//top collision
			//update the position of the ball
			Ogre::Vector3 newPosition = Ogre::Vector3(m_pNode->getPosition().x, gameObject->GetNode()->getPosition().y + gameObject->GetHeight() * 0.5f + m_fRadius + 1, 0.0f);
			m_pNode->setPosition(newPosition);
			Bounce(X_COLLISION);
			//no bottom collision
		}
		else
		{
			if (difference.x >= 0)
			{
				//left side
				Ogre::Vector3 newPosition = Ogre::Vector3(gameObject->GetNode()->getPosition().x - gameObject->GetWidth() * 0.5f - m_fRadius - 1, m_pNode->getPosition().y, 0.0f);
				m_pNode->setPosition(newPosition);
			}
			else
			{
				//right side
				Ogre::Vector3 newPosition = Ogre::Vector3(gameObject->GetNode()->getPosition().x + gameObject->GetWidth() * 0.5f + m_fRadius + 1, m_pNode->getPosition().y, 0.0f);
				m_pNode->setPosition(newPosition);
			}
			Bounce(Y_COLLISION);
		}
		
	}
	return false;
}


