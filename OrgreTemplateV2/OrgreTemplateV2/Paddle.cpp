#include "Paddle.h"
#include <iostream>
/// <summary>
/// Contructor for the paddle.
/// Creates a mesh and a Node, then attach it to the Scene Manager.
/// Set the initial values for our paddle.
/// </summary>
/// <param name="sceneManager">Scene Manager of our game</param>
Paddle::Paddle(Ogre::SceneManager* sceneManager)
{

	m_pEntity = sceneManager->createEntity("cube.mesh");
	m_pNode = sceneManager->createSceneNode("PaddleNode");
	m_pNode->attachObject(m_pEntity);
	m_pNode->setPosition(Ogre::Vector3(0.0f, -300.0f, 0.0f));
	m_pNode->setScale(2.f, 0.4f, 0.4f);

	m_fWidth = m_pEntity->getBoundingBox().getSize().x * m_pNode->getScale().x;
	m_fHeight = m_pEntity->getBoundingBox().getSize().y * m_pNode->getScale().y;
	m_fMoveSpeed = 500;
	m_iLives = 5;
	m_iScore = 0;
}

/// <summary>
/// Function called at the start of every frame.
/// Updates the position of the paddle based on the MoveDirection vector.
/// </summary>
/// <param name="evt"></param>
/// <returns></returns>
bool Paddle::frameStarted(const Ogre::FrameEvent& evt)
{
	float const screenWidth = 560;
	m_pNode->translate(m_vMoveDirection * m_fMoveSpeed * evt.timeSinceLastFrame);
	if (m_pNode->getPosition().x > screenWidth || m_pNode->getPosition().x < -screenWidth)
	{
		m_pNode->translate(-m_vMoveDirection * m_fMoveSpeed * evt.timeSinceLastFrame);
	}
	m_vMoveDirection = m_vMoveDirection * 0.95;
	return true;
}
/// <summary>
/// Returns the Paddle node
/// </summary>
/// <returns></returns>
SceneNode* Paddle::GetNode() 
{
	return m_pNode;
}
/// <summary>
/// Set the direction in which the paddle is going to move
/// </summary>
/// <param name="direction"></param>
void Paddle::SetMoveDirection(Ogre::Vector3 direction)
{
	m_vMoveDirection = direction;
}
/// <summary>
/// Return the current lives of the paddle
/// </summary>
/// <returns></returns>
int Paddle::GetLives()
{
	return m_iLives;
}
/// <summary>
/// Set the amount of lives that the paddle has.
/// </summary>
/// <param name="lives"></param>
void Paddle::SetLives(int lives)
{
	m_iLives = lives;
}
/// <summary>
/// Returns the current score of the paddle
/// </summary>
/// <returns></returns>
int Paddle::GetScore()
{
	return m_iScore;
}
/// <summary>
/// Set the score of the paddle
/// </summary>
/// <param name="score"></param>
void Paddle::SetScore(int score)
{
	m_iScore = score;
}
/// <summary>
/// Get the height of the paddle
/// </summary>
/// <returns></returns>
float Paddle::GetHeight()
{
	return m_fHeight;
}
/// <summary>
/// Get the width of the paddle
/// </summary>
/// <returns></returns>
float Paddle::GetWidth()
{
	return m_fWidth;
}



