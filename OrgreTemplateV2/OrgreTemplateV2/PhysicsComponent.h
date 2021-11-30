#pragma once
#include "Ogre.h"

class PhysicsComponent
{
public:
    void SetPhysicsComponent(Ogre::SceneNode* node);
    void UpdatePhysics(const Ogre::FrameEvent& evt);
    void SetVelocity(Ogre::Vector3 velocity);
    void SetXVelocity(float x);
    void SetYVelocity(float y);

protected:
    
    float c_gravity;
    float c_airFriction;
    
    float xVelocity;
    float zVelocity;

private:
    Ogre::SceneNode* nodeRef;
    Ogre::Vector3 velocity;
    
    
};
