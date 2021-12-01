#include "Game.h"
#include "Player.h"
#include "Platform.h"
#include "Player.h"
#include "UILabels.h"
#include "FollowCamera.h"

Root* Game::g_pRoot = nullptr;
Game::Game() : ApplicationContext("Assigment 02 - Julian Escobar / Lucas Krespi")
{
}

/// <summary>
/// Initialize our application
/// Subscribe our application to the Input Listener.
/// Create m_pRoot and SceneManager.
/// Create all the objects that we are going to use in our game.
/// </summary>
void Game::setup()
{
	
	ApplicationContext::setup();

	addInputListener(this);


	g_pRoot = getRoot();
	m_pScnMgr = g_pRoot->createSceneManager(DefaultSceneManagerFactory::FACTORY_TYPE_NAME,"SceneManager");

	RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(m_pScnMgr);

	
	
	CreateScene();
	CreateUpdate();
	initializePlatforms();
	CreateObjsWithFrameListener();
	CreateCamera();
}
/// <summary>
/// Handle all the input for our application
/// </summary>
/// <param name="evt">Input that we pressed</param>
/// <returns>returns true when there is an input</returns>
bool Game::keyPressed(const KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_ESCAPE:
		getRoot()->queueEndRendering();
		break;
	case 'h':
		m_pSceneLabels->GetTrayManager()->hideCursor();
		break;
	case 'j':
		m_pSceneLabels->GetTrayManager()->showCursor();
		break;
	default:
		break;
	}

	m_pPlayer->HandleInput(evt);

	/*if (m_pPaddle->GetLives() < 1)
	{
		m_pRoot->removeFrameListener(m_pBall);
		m_pRoot->removeFrameListener(m_pPaddle);
	}*/

	return true;
}
/// <summary>
/// Create our Scene Node and the ambient light
/// </summary>
void Game::CreateScene()
{
	Ogre::SceneNode* node = m_pScnMgr->createSceneNode("Node1");
	m_pScnMgr->getRootSceneNode()->addChild(node);
	
	m_pScnMgr->setAmbientLight(ColourValue(1, 1, 1));
}
/// <summary>
/// Creates the camera
/// </summary>
void Game::CreateCamera()
{
	
	//SceneNode* camNode = m_pScnMgr->getRootSceneNode()->createChildSceneNode();


	Camera* cam = m_pScnMgr->createCamera("myCam");
	//cam->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	cam->setNearClipDistance(5);
	cam->setAutoAspectRatio(true);
	//camNode->attachObject(cam);
	//camNode->setPosition(0, 0, 1000);
	//camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);
	getRenderWindow()->addViewport(cam);

	
	FollowCamera* fCam = new FollowCamera(m_pScnMgr, cam);
	fCam->SetFollowedObject(m_pPlayer);
	m_pUpdate->addGameObject(fCam);
}

void Game::CreateUpdate()
{
	m_pUpdate = new Update();
	m_pScnMgr->getRootSceneNode()->addChild(m_pUpdate->GetNode());
	g_pRoot->addFrameListener(m_pUpdate);
}

/// <summary>
/// Create all the objects that we are going to update in our game every frame
/// </summary>
void Game::CreateObjsWithFrameListener()
{
	//Create Ball
	m_pPlayer = new Player();
	m_pScnMgr->getRootSceneNode()->addChild(m_pPlayer->GetNode());

	m_pUpdate->SetPlayerRef(m_pPlayer);
	
	
	//Create Labels
	m_pScnMgr->addRenderQueueListener(mOverlaySystem);
	m_pSceneLabels = new UILabels(getRenderWindow(), m_pPlatform);
	addInputListener(m_pSceneLabels->GetTrayManager());
	g_pRoot->addFrameListener(m_pSceneLabels);

}

void Game::initializePlatforms()
{
	//Create Platforms
	m_pPlatform = new Platform();
	m_pScnMgr->getRootSceneNode()->addChild(m_pPlatform->GetNode());
	
	m_PlatformPool =  ObjectPoolingEngine<Platform>(5);
	for(int i = 0; i< m_PlatformPool.GetSize(); i++)
	{
		Platform* temp = m_PlatformPool.RetrieveObjectFromPool();
		m_pScnMgr->getRootSceneNode()->addChild(temp->GetNode());
		temp->SetPosition(Ogre::Vector3(i *100.0f, i*100.0f,0.0f));
		m_pUpdate->addGameObject(temp);
	}
	
}

void Game::updatePlatforms()
{
}
