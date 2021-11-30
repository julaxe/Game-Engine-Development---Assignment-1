#pragma once
#include "GameObject.h"
#include "Ogre.h"

using namespace Ogre;

//============ Platform CLASS ====================

class Platform : public GameObject
{
public:
	Platform();
private:
	static int s_iId;
};
