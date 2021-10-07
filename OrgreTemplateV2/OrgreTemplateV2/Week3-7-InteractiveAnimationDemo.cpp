//Week3-7-InteractiveAnimationDemo
//We will create a WASD control for Sinbad 
//Now use the translate vector to translate the model, and keep in mind to use time - based and not frame - based movement
//Hooman Salamat


#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

Ogre::Vector3 translate(0, 0, 0);


class Paddle : public Ogre::FrameListener
{
public:
	Paddle(Ogre::SceneManager* sceneManager)
	{
		_node = sceneManager->createSceneNode("Paddle");
		_entity = sceneManager->createEntity("cube.mesh");
		_node->attachObject(_entity);
		_node->setPosition(Ogre::Vector3(0.0f, -300.f, 0.0f));
		_node->setScale(2.f, 0.4f, 0.4f);
		MoveSpeed = 100;
	}
	bool frameStarted(const Ogre::FrameEvent& evt)
	{
		_node->translate(translate* MoveSpeed * evt.timeSinceLastFrame);
		translate = Ogre::Vector3(0, 0, 0);
		return true;
	}
	SceneNode* getNode() { return _node; }

private:
	SceneNode* _node;
	Entity* _entity;
	float MoveSpeed;
};
class OgreTutorial
	: public ApplicationContext
	, public InputListener
{
private:
	SceneNode* SinbadNode;
	SceneManager* scnMgr;
	Root* root;
public:
	OgreTutorial();
	virtual ~OgreTutorial() {}

	void setup();
	bool keyPressed(const KeyboardEvent& evt);
	void createScene();
	void createCamera();
	void createFrameListener();
};


OgreTutorial::OgreTutorial()
	: ApplicationContext("week3-7-InteractiveAnimationDemo")
{
}


void OgreTutorial::setup()
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
	createFrameListener();

	std::cout << "width: " << getRenderWindow()->getWidth() << std::endl;
	std::cout << "height: " << getRenderWindow()->getHeight() << std::endl;

}


bool OgreTutorial::keyPressed(const KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_ESCAPE:
		getRoot()->queueEndRendering();
		break;
	case 'a':
		translate = Ogre::Vector3(-1, 0, 0);
		break;
	case 'd':
		translate = Ogre::Vector3(1, 0, 0);
		break;
	default:
		break;
	}
	return true;
}

void OgreTutorial::createScene()
{
	// -- tutorial section start --

	Ogre::SceneNode* node = scnMgr->createSceneNode("Node1");
	scnMgr->getRootSceneNode()->addChild(node);

	scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

	//! [turnlights]
	scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
	//! [turnlights]

 //! [newlight]
 //

	Ogre::Light* light = scnMgr->createLight("Light1");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(0, 0, -1));

	// Set Light Color
	light->setDiffuseColour(1.0f, 1.0f, 1.0f);
	// Set Light Reflective Color
	light->setSpecularColour(1.0f, 1.0f, 0.0f);
	// Set Light (Range, Brightness, Fade Speed, Rapid Fade Speed)
	//light1->setAttenuation(10, 0.5, 0.045, 0.0);

	//
	Entity* lightEnt = scnMgr->createEntity("LightEntity", "sphere.mesh");
	SceneNode* lightNode = node->createChildSceneNode("LightNode");
	//lightNode->attachObject(lightEnt);
	lightNode->attachObject(light);
	lightNode->setScale(0.01f, 0.01f, 0.01f);

	//! [newlight]
	//The first thing we'll do is create an abstract Plane object. This is not the mesh, it is more of a blueprint.
	Plane plane(Vector3::UNIT_Y, -10);
	//Now we'll ask the MeshManager to create us a mesh using our Plane blueprint. The MeshManager is already keeping track of the resources we loaded when initializing our application. On top of this, it can create new meshes for us.
	MeshManager::getSingleton().createPlane(
		"ground", RGN_DEFAULT,
		plane,
		1500, 1500, 20, 20,
		true,
		1, 5, 5,
		Vector3::UNIT_Z);

	//Now we will create a new Entity using this mesh.
	//We want to tell our SceneManager not to cast shadows from our ground Entity. It would just be a waste. Don't get confused, this means the ground won't cast a shadow, it doesn't mean we can't cast shadows on to the ground.
	Entity* groundEntity = scnMgr->createEntity("ground");
	//scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setCastShadows(false);
	//And finally we need to give our ground a material.
	groundEntity->setMaterialName("Examples/BeachStones");

	//Character creation
	Entity* ent = scnMgr->createEntity("Sinbad.mesh");
	ent->setCastShadows(true);
	SinbadNode = scnMgr->createSceneNode("Character");
	//SinbadNode->attachObject(ent);
	scnMgr->getRootSceneNode()->addChild(SinbadNode);
	SinbadNode->setPosition(Ogre::Vector3(0.0f, 4.0f, 0.0f));
	SinbadNode->setScale(3.0f, 3.0f, 3.0f);

	


}

void OgreTutorial::createCamera()
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

void OgreTutorial::createFrameListener()
{
	//Create Paddle
	Paddle* _paddle = new Paddle(scnMgr);
	scnMgr->getRootSceneNode()->addChild(_paddle->getNode());
	mRoot->addFrameListener(_paddle);
}

int main(int argc, char** argv)
{
	try
	{
		OgreTutorial app;
		app.initApp();
		app.getRoot()->startRendering();
		app.closeApp();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred during execution: " << e.what() << '\n';
		return 1;
	}

	return 0;
}

