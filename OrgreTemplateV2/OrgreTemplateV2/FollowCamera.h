#pragma once
#include "Ogre.h"
#include "GameObject.h"

class FollowCamera : public GameObject
{
public:
	FollowCamera(Ogre::SceneManager* sceneManager, Camera* cam);

	void SetFollowedObject(GameObject* Object);
	void Update(const FrameEvent& evt) override;
	

private:
	
	GameObject* m_pFollowedObject;
	Ogre::Vector3 m_vFollowPosition;
	Ogre::Vector3 m_vCameraArm;

	SceneNode* camNode;	
};

