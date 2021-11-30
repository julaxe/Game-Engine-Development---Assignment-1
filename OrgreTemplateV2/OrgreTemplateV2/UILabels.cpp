#include "UILabels.h"
//============ LABEL CLASS ====================
/// <summary>
///	Constructor of the UIlabels.
/// Initialize the tray manager.
/// Set the UI elements that are going to be included in the game window.
/// </summary>
UILabels::UILabels(Ogre::RenderWindow* rendererWindow, Platform* paddle)
{
	m_pmTrayManager = new OgreBites::TrayManager("Title", rendererWindow);

	//set up of UI preferences
	m_pmTrayManager->showFrameStats(OgreBites::TL_BOTTOMRIGHT);
	m_pmTrayManager->toggleAdvancedFrameStats();


	m_pPaddle = paddle;

	m_tTimer = Ogre::Timer();
	m_plTimerText = m_pmTrayManager->createLabel(OgreBites::TL_TOP, "timerText", "Timer", 100);
	m_plTime = m_pmTrayManager->createLabel(OgreBites::TL_TOP, "time", " ", 100);


	//Populating array of strings to display
	m_svParamNames.push_back("Score");
	m_svParamNames.push_back("Lives");

	m_pPanel = m_pmTrayManager->createParamsPanel(OgreBites::TL_TOPLEFT, "ScoreBoard", 150, m_svParamNames);

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
	m_pPanel->setParamValue(0, Ogre::StringConverter::toString(m_pPaddle->GetScore()));
	m_pPanel->setParamValue(1, Ogre::StringConverter::toString(m_pPaddle->GetLives()));

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

