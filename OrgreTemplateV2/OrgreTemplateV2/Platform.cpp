#include "Platform.h"
#include <iostream>
/// <summary>
/// Contructor for the Platform.
/// Creates a mesh and a Node, then attach it to the Scene Manager.
/// Set the initial values for our Platform.
/// </summary>
/// <param name="sceneManager">Scene Manager of our game</param>
Platform::Platform(Ogre::SceneManager* sceneManager)
{

	m_pEntity = sceneManager->createEntity("cube.mesh");
	m_pNode = sceneManager->createSceneNode("PaddleNode");
	m_pNode->attachObject(m_pEntity);
	m_pNode->setPosition(Ogre::Vector3(0.0f, 0.0f, 0.0f));
	m_pNode->setScale(2.f, 0.4f, 0.4f);

	m_fWidth = m_pEntity->getBoundingBox().getSize().x * m_pNode->getScale().x;
	m_fHeight = m_pEntity->getBoundingBox().getSize().y * m_pNode->getScale().y;
	m_fMoveSpeed = 500;
	m_iLives = 5;
	m_iScore = 0;
}

/// <summary>
/// Function called at the start of every frame.
/// Updates the position of the Platform based on the MoveDirection vector.
/// </summary>
/// <param name="evt"></param>
/// <returns></returns>
bool Platform::frameStarted(const Ogre::FrameEvent& evt)
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
/// Returns the Platform node
/// </summary>
/// <returns></returns>
SceneNode* Platform::GetNode() 
{
	return m_pNode;
}
/// <summary>
/// Set the direction in which the Platform is going to move
/// </summary>
/// <param name="direction"></param>
void Platform::SetMoveDirection(Ogre::Vector3 direction)
{
	m_vMoveDirection = direction;
}
/// <summary>
/// Return the current lives of the Platform
/// </summary>
/// <returns></returns>
int Platform::GetLives()
{
	return m_iLives;
}
/// <summary>
/// Set the amount of lives that the Platform has.
/// </summary>
/// <param name="lives"></param>
void Platform::SetLives(int lives)
{
	m_iLives = lives;
}
/// <summary>
/// Returns the current score of the Platform
/// </summary>
/// <returns></returns>
int Platform::GetScore()
{
	return m_iScore;
}
/// <summary>
/// Set the score of the Platform
/// </summary>
/// <param name="score"></param>
void Platform::SetScore(int score)
{
	m_iScore = score;
}
/// <summary>
/// Get the height of the Platform
/// </summary>
/// <returns></returns>
float Platform::GetHeight()
{
	return m_fHeight;
}
/// <summary>
/// Get the width of the Platform
/// </summary>
/// <returns></returns>
float Platform::GetWidth()
{
	return m_fWidth;
}



