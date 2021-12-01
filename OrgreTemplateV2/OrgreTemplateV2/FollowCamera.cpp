#include "FollowCamera.h"


FollowCamera::FollowCamera(Ogre::SceneManager* sceneManager, Camera* cam)
{
	camNode = sceneManager->getRootSceneNode()->createChildSceneNode();

	camNode->attachObject(cam);
	camNode->setPosition(m_vFollowPosition + m_vCameraArm);
	camNode->lookAt(m_vFollowPosition, Node::TS_WORLD);

	m_vCameraArm = Ogre::Vector3(0, 1000, 1000);
}

void FollowCamera::SetFollowedObject(GameObject* Object)
{
	m_pFollowedObject = Object;
}

void FollowCamera::Update(const FrameEvent& evt)
{
	m_vFollowPosition = m_pFollowedObject->GetPosition();

	camNode->setPosition(Ogre::Math::lerp(camNode->getPosition(), m_vFollowPosition + m_vCameraArm, 0.1f));
	camNode->lookAt(m_vFollowPosition, Node::TS_WORLD);
}

