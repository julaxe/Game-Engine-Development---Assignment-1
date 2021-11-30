#pragma once
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "Ogre.h"
#include "OgreRTShaderSystem.h"
#include <iostream>

class Platform;
class Ball;
class UILabels;
using namespace Ogre;
using namespace OgreBites;

class Game : public ApplicationContext, public InputListener
{
private:
	Platform* m_pPlatform;
	Ball* m_pBall;
	UILabels* m_pSceneLabels;
	SceneManager* m_pScnMgr;
	Root* m_pRoot;

public:
	Game();
	virtual ~Game() {}

	void setup() override;
	bool keyPressed(const KeyboardEvent& evt) override;
	void CreateScene();
	void CreateCamera();
	void CreateObjsWithFrameListener();
};


