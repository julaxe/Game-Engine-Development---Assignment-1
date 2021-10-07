/*-------------------------------------------------------------------------
Simple Entity Demo
During the startRendering() function call, Ogre gathers all the objects, lights, and
materials that are to be drawn from the scene manager based on the camera's frustum or
visible bounds. It then passes that information to the render system, which executes the 3D
library function calls that run on your system's graphics hardware, to do the actual drawing on
a render surface. In our case, the 3D library is Direct X or OpenGL
-------------------------------------------------------------------------*/

//! [fullsource]

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

class Paddle
{
public:
    Paddle(Ogre::SceneManager* sceneManager)
    {
        _node = sceneManager->createSceneNode("Paddle");
        _entity = sceneManager->createEntity("cube.mesh");
        _node->attachObject(_entity);
        _node->setPosition(Ogre::Vector3(0.0f, 0.0f, 0.0f));
        _node->setScale(0.1f, 0.1f, 0.1f);
    }
    SceneNode* getNode() { return _node; }
    

    
private:
    SceneNode* _node;
    Entity* _entity;
};

class BrickGameLucasAndJulian
    : public ApplicationContext
    , public InputListener
{
public:
    BrickGameLucasAndJulian();
    virtual ~BrickGameLucasAndJulian() {}

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
};


BrickGameLucasAndJulian::BrickGameLucasAndJulian()
    : ApplicationContext("simpleSample")
{
}


void BrickGameLucasAndJulian::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    Root* root = getRoot();
    SceneManager* scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // -- tutorial section start --
    //! [turnlights]
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    //! [turnlights]

    //! [newlight]
    Light* light = scnMgr->createLight("MainLight");
    SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(light);
    //! [newlight]

    //! [lightpos]
    lightNode->setPosition(20, 80, 49);
    //! [lightpos]

    //! [camera]
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);

    //YOU COULD ALSO SET THE ASPECT RATIO
    // cam->setAspectRatio(Ogre::Real(rect.right - rect.left) /
    //  Ogre::Real(rect.bottom - rect.top));

    camNode->attachObject(cam);
    camNode->setPosition(0, 0, 140);

    // and tell it to render into the main window
    //getRenderWindow()->addViewport(cam);

    //YOU COULD ALSO CHANGE THE VIEWPORT BACKGROUND
       Ogre::Viewport* Viewport = NULL;
    if (0 == getRenderWindow()->getNumViewports()) {
        Viewport = getRenderWindow()->addViewport(cam);
        Viewport->setBackgroundColour(Ogre::ColourValue(0.8f, 1.0f, 0.8f));
    }



    //! [camera]

    //! [entity1]
    Entity* ogreEntity = scnMgr->createEntity("ogrehead.mesh");
    //! [entity1]

    //! [entity1node]
    SceneNode* ogreNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    //! [entity1node]

    //! [entity1nodeattach]
    ogreNode->attachObject(ogreEntity);
    //! [entity1nodeattach]

    //! [cameramove]
    camNode->setPosition(0, 47, 222);
    //! [cameramove]


    // -- tutorial section end --
}


bool BrickGameLucasAndJulian::keyPressed(const KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    return true;
}


int main(int argc, char** argv)
{
    try
    {
        BrickGameLucasAndJulian app;
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

//! [fullsource]
