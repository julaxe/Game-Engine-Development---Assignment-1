#pragma once
#include "Ogre.h"

using namespace Ogre;

//============ Platform CLASS ====================

class Platform : public Ogre::FrameListener
{
public:

	Platform(Ogre::SceneManager* sceneManager);

	SceneNode* GetNode();

	void SetMoveDirection(Ogre::Vector3 direction);

	int GetLives();
	void SetLives(int lives);

	int GetScore();
	void SetScore(int score);

	float GetHeight();
	float GetWidth();

private:
	
	bool frameStarted(const Ogre::FrameEvent& evt) override;

private:

	SceneNode* m_pNode;
	Entity* m_pEntity;

	float m_fWidth;
	float m_fHeight;

	float m_fMoveSpeed;
	Ogre::Vector3 m_vMoveDirection;

	int m_iLives;
	int m_iScore;
};
