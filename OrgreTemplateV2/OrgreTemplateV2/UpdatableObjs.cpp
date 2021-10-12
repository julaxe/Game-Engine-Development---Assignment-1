
#include "UpdatableObjs.h"

Paddle::Paddle(Ogre::SceneManager* sceneManager)
{

	_entity = sceneManager->createEntity("cube.mesh");
	
	//Create Manual Mesh Fail :(
	//_manualObjPaddle = NULL;
	//_manualObjPaddle = sceneManager->createManualObject("Paddle");
	//_manualObjPaddle->setDynamic(false);
	//_manualObjPaddle->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);
	//_manualObjPaddle->position(-1, -2, 0);
	//_manualObjPaddle->position(-1, 2, 0);
	//_manualObjPaddle->position(1, 2, 0);
	//_manualObjPaddle->position(1, -2, 0);
	//_manualObjPaddle->quad(0, 1, 2, 3);
	//_manualObjPaddle->end();

	_node = sceneManager->createSceneNode("PaddleNode");
	_node->attachObject(_entity);
	_node->setPosition(Ogre::Vector3(0.0f, -300.0f, 0.0f));
	_node->setScale(2.f, 0.4f, 0.4f);
	moveSpeed = 500;
	lives = 5;
	score = 0;
}

bool Paddle::frameStarted(const Ogre::FrameEvent& evt)
{
	_node->translate(moveDirection * moveSpeed * evt.timeSinceLastFrame);
	moveDirection = moveDirection * 0.98;
	return true;
}

SceneNode* Paddle::GetNode() 
{
	return _node;
}

void Paddle::SetMoveDirection(Ogre::Vector3 direction)
{
	moveDirection = direction;
}

int Paddle::GetLives()
{
	return lives;
}

int Paddle::GetScore()
{
	return score;
}


//============ BALL CLASS ====================



//============ LABEL CLASS ====================

UILabels::UILabels(Ogre::RenderWindow* rendererWindow, Paddle* paddle)
{
	_mTrayManager = new OgreBites::TrayManager("Title", rendererWindow);

	//set up of UI preferences
	_mTrayManager->showFrameStats(OgreBites::TL_BOTTOMRIGHT);
	_mTrayManager->toggleAdvancedFrameStats();
	//_mTrayManager->hideCursor();

	paddleTest = paddle;

	timer = Ogre::Timer();
	counter = 0;
	_timerText = _mTrayManager->createLabel(OgreBites::TL_TOP, "timerText", "TIMER", 100);
	_time = _mTrayManager->createLabel(OgreBites::TL_TOP, "time", " ", 100);


	//Populating array of strings to display
	_paramNames.push_back("Score");
	_paramNames.push_back("Lives");

	_panel = _mTrayManager->createParamsPanel(OgreBites::TL_TOPLEFT, "ScoreBoard", 150, _paramNames);

}

bool UILabels::frameStarted(const Ogre::FrameEvent& evt)
{

	if ((counter % 60) == 0)
	{
		_time->setCaption(Ogre::StringConverter().toString(timer.getMilliseconds()/1000));
		counter = 0;

		_panel->setParamValue(0, Ogre::StringConverter::toString(paddleTest->GetScore()));
		_panel->setParamValue(1, Ogre::StringConverter::toString(paddleTest->GetLives()));
	}

	counter++;

	return true;
}

OgreBites::TrayManager* UILabels::GetTrayManager()
{
	return _mTrayManager;
}

void UILabels::RefreshUI(int lives, int score)
{
	
}
