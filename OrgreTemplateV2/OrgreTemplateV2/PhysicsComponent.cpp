#include "PhysicsComponent.h"


void PhysicsComponent::SetPhysicsComponent(Ogre::SceneNode* node)
{
    nodeRef = node;
}

void PhysicsComponent::UpdatePhysics(const Ogre::FrameEvent& evt)
{
    Ogre::Vector3 initialPos = nodeRef->getPosition();
    velocity.x = Ogre::Math::lerp(velocity.x, 0.0f, c_airFriction);
    velocity.y = velocity.y + (-c_gravity *evt.timeSinceLastFrame);
    velocity.z = Ogre::Math::lerp(velocity.z, 0.0f, c_airFriction);
    Ogre::Vector3 newPosition = initialPos + velocity*evt.timeSinceLastFrame;
    nodeRef->setPosition(newPosition);
}

void PhysicsComponent::SetVelocity(Ogre::Vector3 velocity)
{
    this->velocity = velocity;
}

void PhysicsComponent::SetXVelocity(float x)
{
    velocity.x = x;
}

void PhysicsComponent::SetYVelocity(float y)
{
    velocity.y = y;
}

void PhysicsComponent::SetZVelocity(float z)
{
    velocity.z = z;
}

Ogre::Vector3 PhysicsComponent::GetVelocity()
{
    return velocity;
}
