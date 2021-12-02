#pragma once
#include "GameObject.h"
#include "Ogre.h"

using namespace Ogre;

//============ Platform CLASS ====================

class Platform : public GameObject
{
public:
	Platform();
	void Update(const FrameEvent& evt) override;
private:
	static int s_iId;
};
