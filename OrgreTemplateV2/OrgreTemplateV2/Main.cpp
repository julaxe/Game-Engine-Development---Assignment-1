#include "Game.h"

/*!
 Main Game Class
 It contains the main game loop.
*/
int main(int argc, char** argv)
{
	try
	{
		Game::Instance()->initApp();
		Game::Instance()->getRoot()->startRendering();
		Game::Instance()->closeApp();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred during execution: " << e.what() << '\n';
		return 1;
	}

	return 0;
}

