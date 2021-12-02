#include "FollowCamera.h"
#include "Game.h"


FollowCamera::FollowCamera(Camera* cam)
{
	m_PlayerRef = nullptr;
	camNode = Game::g_pRoot->getSceneManager("SceneManager")->getRootSceneNode()->createChildSceneNode();
	camNode->attachObject(cam);
	m_vCameraArm = Ogre::Vector3(0, 1000, 1000);
	SetTag(GameObjectTag::Camera);
}

void FollowCamera::SetFollowedObject(Player* playerRef)
{
	m_PlayerRef = playerRef;
	camNode->setPosition(m_PlayerRef->GetNode()->getPosition() + m_vCameraArm);
	camNode->lookAt(m_PlayerRef->GetNode()->getPosition(), Node::TS_WORLD);
}

void FollowCamera::Update(const FrameEvent& evt)
{
	Vector3 desiredPos = m_PlayerRef->GetNode()->getPosition() + m_vCameraArm;
	if(m_PlayerRef->GetVelocity().y < 0)
	{
		camNode->setPosition(Ogre::Math::lerp(camNode->getPosition(),
			Vector3(desiredPos.x,camNode->getPosition().y, desiredPos.z), 0.1f));
	}
	else
	{
		camNode->setPosition(Ogre::Math::lerp(camNode->getPosition(), desiredPos, 0.1f));
	}
}

