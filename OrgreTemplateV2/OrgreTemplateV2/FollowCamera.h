#pragma once
#include "Ogre.h"
#include "Player.h"

class FollowCamera : public GameObject
{
public:
	FollowCamera(Camera* cam);

	void SetFollowedObject(Player* playerRef);
	void Update(const FrameEvent& evt) override;
	

private:
	
	Player* m_PlayerRef;
	Ogre::Vector3 m_vCameraArm;

	SceneNode* camNode;	
};

