#pragma once
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "UpdatableObjs.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

class Game : public ApplicationContext, public InputListener, public FrameListener
{
private:
	Paddle* _paddle;
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
	void createMeshWithFrameListener();
	//bool frameStarted(const Ogre::FrameEvent& evt) override;
};


