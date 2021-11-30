#pragma once
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "Ogre.h"
#include "ObjectPoolingEngine.h"
#include "OgreRTShaderSystem.h"
#include "Update.h"
#include <iostream>

class Platform;
class Player;
class UILabels;
using namespace Ogre;
using namespace OgreBites;

class Game : public ApplicationContext, public InputListener
{
private:
	Update* m_pUpdate;
	Platform* m_pPlatform;
	Player* m_pPlayer;
	UILabels* m_pSceneLabels;
	SceneManager* m_pScnMgr;
	ObjectPoolingEngine<Platform> m_PlatformPool;

public:
	static Root* g_pRoot;
	
public:
	Game();
	virtual ~Game() {}
	

	void setup() override;
	bool keyPressed(const KeyboardEvent& evt) override;
	void CreateScene();
	void CreateCamera();
	void CreateUpdate();
	void CreateObjsWithFrameListener();

private:
	void initializePlatforms();
	void updatePlatforms();
};


