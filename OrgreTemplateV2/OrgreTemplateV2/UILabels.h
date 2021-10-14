#pragma once
#include "Paddle.h"
#include "OgreTrays.h"
//============ LABEL CLASS ====================
class UILabels : public Ogre::FrameListener
{
public:

	UILabels(Ogre::RenderWindow* rendererWindow, Paddle* paddle);

	OgreBites::TrayManager* GetTrayManager();

private:

	bool frameStarted(const Ogre::FrameEvent& evt) override;

private:
	Paddle* m_pPaddle;
	OgreBites::TrayManager* m_pmTrayManager;
	StringVector m_svParamNames;
	OgreBites::Label* m_plTimerText;
	OgreBites::Label* m_plTime;
	Timer m_tTimer;
	OgreBites::ParamsPanel* m_pPanel;
};