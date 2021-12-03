#pragma once
#include "OgreTrays.h"
#include "Player.h"

//============ LABEL CLASS ====================
class UILabels : public Ogre::FrameListener
{
public:

	UILabels(Ogre::RenderWindow* rendererWindow, Player* player);

	OgreBites::TrayManager* GetTrayManager();

private:

	bool frameStarted(const Ogre::FrameEvent& evt) override;

private:
	Player* m_playerRef;
	OgreBites::TrayManager* m_pmTrayManager;
	StringVector m_svParamNames;
	OgreBites::Label* m_plTimerText;
	OgreBites::Label* m_plTime;
	Timer m_tTimer;
	OgreBites::ParamsPanel* m_pPanel;
};
