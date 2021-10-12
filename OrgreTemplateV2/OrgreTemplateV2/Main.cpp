//Week3-7-InteractiveAnimationDemo
//We will create a WASD control for Sinbad 
//Now use the translate vector to translate the model, and keep in mind to use time - based and not frame - based movement
//Hooman Salamat

#include "Game.h"


int main(int argc, char** argv)
{
	try
	{
		Game app;
		app.initApp();
		app.getRoot()->startRendering();
		app.closeApp();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred during execution: " << e.what() << '\n';
		return 1;
	}

	return 0;
}

