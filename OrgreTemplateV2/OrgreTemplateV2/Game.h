#pragma once
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "UpdatableObjs.h"

using namespace Ogre;
using namespace OgreBites;

class Game : public ApplicationContext, public InputListener
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
};


