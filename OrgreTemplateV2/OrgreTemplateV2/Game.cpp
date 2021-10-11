#include "Game.h"

Game::Game() : ApplicationContext("Assigment 01 - Julian Escobar / Lucas Krespi")
{
}

void Game::setup()
{
	// do not forget to call the base first
	ApplicationContext::setup();
	addInputListener(this);

	// get a pointer to the already created root
	root = getRoot();
	scnMgr = root->createSceneManager();


	// register our scene with the RTSS
	RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);

	createScene();
	createCamera();
	createMeshWithFrameListener();
}

bool Game::keyPressed(const KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_ESCAPE:
		getRoot()->queueEndRendering();
		break;
	case 'a':
		_paddle->SetMoveDirection(Ogre::Vector3(-1, 0, 0));
		break;
	case 'd':
		_paddle->SetMoveDirection(Ogre::Vector3(1, 0, 0));
		break;
	default:
		break;
	}
	return true;
}

void Game::createScene()
{
	Ogre::SceneNode* node = scnMgr->createSceneNode("Node1");
	scnMgr->getRootSceneNode()->addChild(node);

	//scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

	//! [turnlights]
	scnMgr->setAmbientLight(ColourValue(1, 1, 1));
}

void Game::createCamera()
{
	//! [camera]
	SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

	// create the camera
	Camera* cam = scnMgr->createCamera("myCam");
	cam->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);
	camNode->setPosition(0, 0, 50);
	camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);

	// and tell it to render into the main window
	getRenderWindow()->addViewport(cam);

	//! [camera]
	
}

void Game::createMeshWithFrameListener()
{
	//Create Paddle
	_paddle = new Paddle(scnMgr);
	scnMgr->getRootSceneNode()->addChild(_paddle->GetNode());
	mRoot->addFrameListener(_paddle);

	scnMgr->addRenderQueueListener(mOverlaySystem);
	_sceneLabels = new UILabels(getRenderWindow());
	addInputListener(_sceneLabels->GetTrayManager());
	mRoot->addFrameListener(_sceneLabels);

}
