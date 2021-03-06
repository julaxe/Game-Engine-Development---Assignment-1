#include "UILabels.h"
//============ LABEL CLASS ====================
/// <summary>
///	Constructor of the UIlabels.
/// Initialize the tray manager.
/// Set the UI elements that are going to be included in the game window.
/// </summary>
UILabels::UILabels(Ogre::RenderWindow* rendererWindow, Player* player)
{
	m_pmTrayManager = new OgreBites::TrayManager("Title", rendererWindow);

	//set up of UI preferences
	m_pmTrayManager->showFrameStats(OgreBites::TL_BOTTOMRIGHT);
	m_pmTrayManager->toggleAdvancedFrameStats();


	m_playerRef = player;

	m_tTimer = Ogre::Timer();
	m_plTimerText = m_pmTrayManager->createLabel(OgreBites::TL_TOP, "timerText", "Timer", 100);
	m_plTime = m_pmTrayManager->createLabel(OgreBites::TL_TOP, "time", " ", 100);


	//Populating array of strings to display
	m_svParamNames.push_back("Score");
	m_svParamNames.push_back("Lives");

	m_pPanel = m_pmTrayManager->createParamsPanel(OgreBites::TL_TOPLEFT, "ScoreBoard", 150, m_svParamNames);
	hasLost = false;

	m_plResete = m_pmTrayManager->createLabel(OgreBites::TL_CENTER, "reset label", "Press r to reset", 200);
	m_pmTrayManager->getTrayContainer(OgreBites::TL_CENTER)->hide();
}
/// <summary>
/// Function called at the start of every frame.
/// Update the UI elements.
/// </summary>
/// <param name="evt"></param>
/// <returns></returns>
bool UILabels::frameStarted(const Ogre::FrameEvent& evt)
{


	m_plTime->setCaption(Ogre::StringConverter().toString(m_tTimer.getMilliseconds() / 1000));
	m_pPanel->setParamValue(0, Ogre::StringConverter::toString(m_playerRef->GetScore()));
	m_pPanel->setParamValue(1, Ogre::StringConverter::toString(m_playerRef->GetLifes()));


	if (m_playerRef->GetLifes() <= 0 && !hasLost)
	{
		
		m_pmTrayManager->getTrayContainer(OgreBites::TL_CENTER)->show();
		hasLost = true;
	}

	return true;
}
/// <summary>
/// Returns the tray manager.
/// </summary>
/// <returns></returns>
OgreBites::TrayManager* UILabels::GetTrayManager()
{
	return m_pmTrayManager;
}

