#pragma once
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "UpdatableObjs.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

class Game : public ApplicationContext, public InputListener
{
private:
	Paddle* _paddle;
	Ball* _ball;
	UILabels* _sceneLabels;
	SceneManager* scnMgr;
	Root* root;
public:
	Game();
	virtual ~Game() {}

	void setup();
	bool keyPressed(const KeyboardEvent& evt);
	void createScene();
	void createCamera();
	void createObjsWithFrameListener();
};


