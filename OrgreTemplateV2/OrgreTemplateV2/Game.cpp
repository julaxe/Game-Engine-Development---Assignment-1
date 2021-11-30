#include "Game.h"
#include "Ball.h"
#include "Platform.h"
#include "UILabels.h"
#include "ObjectPoolingEngine.h"

Game::Game() : ApplicationContext("Assigment 01 - Julian Escobar / Lucas Krespi")
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


	m_pRoot = getRoot();
	m_pScnMgr = m_pRoot->createSceneManager();

	RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(m_pScnMgr);

	ObjectPoolingEngine<int>* newPool = nullptr;
	newPool = new ObjectPoolingEngine<int>(5);
	for(int i = 0; i< 6; i++)
	{
		newPool->RetrieveObjectFromPool();
	}
	int* test = newPool->RetrieveObjectFromPool();
	newPool->ThrowBackObjectToPool(test);
	
	CreateScene();
	CreateCamera();
	CreateObjsWithFrameListener();
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
	
	SceneNode* camNode = m_pScnMgr->getRootSceneNode()->createChildSceneNode();


	Camera* cam = m_pScnMgr->createCamera("myCam");
	//cam->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	cam->setNearClipDistance(5);
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);
	camNode->setPosition(0, 0, 1000);
	camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);

	getRenderWindow()->addViewport(cam);

	
}
/// <summary>
/// Create all the objects that we are going to update in our game every frame
/// </summary>
void Game::CreateObjsWithFrameListener()
{

	//Create Paddle
	m_pPlatform = new Platform(m_pScnMgr);
	m_pScnMgr->getRootSceneNode()->addChild(m_pPlatform->GetNode());
	m_pRoot->addFrameListener(m_pPlatform);

	//Create Ball
	m_pBall = new Ball(m_pScnMgr);
	m_pScnMgr->getRootSceneNode()->addChild(m_pBall->GetNode());
	m_pRoot->addFrameListener(m_pBall);


	//Create Labels
	m_pScnMgr->addRenderQueueListener(mOverlaySystem);
	m_pSceneLabels = new UILabels(getRenderWindow(), m_pPlatform);
	addInputListener(m_pSceneLabels->GetTrayManager());
	m_pRoot->addFrameListener(m_pSceneLabels);

}
