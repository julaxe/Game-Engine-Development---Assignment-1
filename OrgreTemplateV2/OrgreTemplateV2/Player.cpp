#include "Player.h"
#include <iostream>

#include "Game.h"
#include "Platform.h"
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
	
	m_pEntity = Game::g_pRoot->getSceneManager("SceneManager")->createEntity("sphere.mesh");
	m_pNode = Game::g_pRoot->getSceneManager("SceneManager")->createSceneNode("BallNode");
	
	m_pEntity->setMaterial(Ogre::MaterialManager::getSingleton().getByName("MyMaterial5"));
	m_pNode->attachObject(m_pEntity);
	m_pNode->setPosition(Ogre::Vector3(0.0f, 300.0f, 0.0f));
	m_pNode->setScale(0.3f, 0.3f, 0.3f);
	//m_pNode->showBoundingBox(true);
	
	//initial values
	m_fRadius = m_pEntity->getBoundingBox().getSize().x * m_pNode->getScale().x * 0.5f;
	m_fMoveSpeed = 400.0f;
	m_iScore = 0;
	m_iLifes = 3;
	m_vInitalPosition = m_pNode->_getDerivedPosition();

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
	case 'w':
		SetZVelocity(-m_fMoveSpeed);
		break;
	case 's':
		SetZVelocity(m_fMoveSpeed);
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
	
	if(GetNode()->getPosition().y > m_iScore)
	{
		m_iScore = GetNode()->getPosition().y;
	}
	if(GetNode()->getPosition().y < Game::Instance()->GetBottomPlatform()->GetNode()->getPosition().y - 500.0f)
	{
		ResetPositionToBottomPlatform();
	}
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

void Player::SetScore(int score)
{
	m_iScore = score;
}

int Player::GetScore()
{
	return m_iScore;
}

void Player::SetLifes(int lifes)
{
	m_iLifes = lifes;
}

int Player::GetLifes()
{
	return m_iLifes;
}

Ogre::Vector3 Player::GetInitialPosition()
{
	return m_vInitalPosition;
}

void Player::ResetPositionToBottomPlatform()
{
	//get bottom platform
	Platform* topPlatform = Game::Instance()->GetTopPlatform();
	//reset the object to the bottom platform
	const Vector3 OnTopBottomPlatform = Vector3(topPlatform->GetNode()->getPosition().x, topPlatform->GetNode()->getPosition().y + 50.0f, topPlatform->GetNode()->getPosition().z);
	GetNode()->setPosition(OnTopBottomPlatform);
	SetVelocity(Vector3(0.0f, 0.0f, 0.0f));

	
	SetLifes(GetLifes() - 1);
	
}

/// <summary>
/// Check for collision with the screen or the paddle.
/// </summary>
/// <returns></returns>
bool Player::CheckForCollision(GameObject* gameObject)
{
	return CheckCollisionWithGameObject(gameObject);

}

float Player::GetRadius()
{
	return m_fRadius;
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
	//get center point circle first
	Ogre::Vector3 center = m_pNode->getPosition();

	//calculate AABB info (center, half-extents);
	Ogre::Vector3 aabb_half_entents = Ogre::Vector3(gameObject->GetWidth(), gameObject->GetHeight(), gameObject->GetLength()) * 0.5;
	Ogre::Vector3 aabb_center = gameObject->GetNode()->_getDerivedPosition();

	//get difference vectro beween both centers;
	Ogre::Vector3 difference = center - aabb_center;
	Ogre::Vector3 clamped = Ogre::Vector3(Ogre::Math::Clamp<Real>(difference.x, -aabb_half_entents.x, aabb_half_entents.x),
		Ogre::Math::Clamp<Real>(difference.y, -aabb_half_entents.y, aabb_half_entents.y), Ogre::Math::Clamp<Real>(difference.z, -aabb_half_entents.z, aabb_half_entents.z));

	//add value to aabb center and we get the value of box closest to circle
	Ogre::Vector3 closest = aabb_center + clamped;
	//retrieve vector between center circle and closest point AABB and check if lenght <= m_fRadius
	difference = closest - center;

	if (difference.length() < m_fRadius)
	{
		
		return true;
		//no bottom collision
		
	}
	return false;
}


