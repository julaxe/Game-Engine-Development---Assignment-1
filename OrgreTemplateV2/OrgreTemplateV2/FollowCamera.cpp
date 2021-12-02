#include "FollowCamera.h"
#include "Game.h"


FollowCamera::FollowCamera(Camera* cam)
{
	m_pFollowedObject = nullptr;
	camNode = Game::g_pRoot->getSceneManager("SceneManager")->getRootSceneNode()->createChildSceneNode();
	camNode->attachObject(cam);
	m_vCameraArm = Ogre::Vector3(0, 1000, 1000);
	SetTag(GameObjectTag::Camera);
}

void FollowCamera::SetFollowedObject(GameObject* Object)
{
	m_pFollowedObject = Object;
	m_vFollowPosition = m_pFollowedObject->GetPosition();
	camNode->setPosition(m_vFollowPosition + m_vCameraArm);
	camNode->lookAt(m_vFollowPosition, Node::TS_WORLD);
}

void FollowCamera::Update(const FrameEvent& evt)
{
	m_vFollowPosition = m_pFollowedObject->GetPosition();

	camNode->setPosition(Ogre::Math::lerp(camNode->getPosition(), m_vFollowPosition + m_vCameraArm, 0.1f));
}

