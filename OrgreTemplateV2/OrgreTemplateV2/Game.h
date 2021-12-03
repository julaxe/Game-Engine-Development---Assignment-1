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
	ObjectPoolingEngine<Platform>* m_PlatformPool;

	int m_PlatformCounter;

	static Game* instance;

public:
	static Root* g_pRoot;
	
public:
	virtual ~Game() {}
	
	static Game* Instance()
	{
		if(instance == nullptr)
		{
			instance = new Game();
		}
		return instance;
	}
	void setup() override;
	bool keyPressed(const KeyboardEvent& evt) override;
	void CreateScene();
	void CreateCamera();
	void CreateUpdate();
	
	ObjectPoolingEngine<Platform>* GetPlatformsPool();
	Platform* GetBottomPlatform();
	Platform* GetTopPlatform();
	Player* GetPlayer();
	void CreateObjsWithFrameListener();
	void GenerateNewPlatform();

private:
	Game();
	void initializePlatforms();
};


