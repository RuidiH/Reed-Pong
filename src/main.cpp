// Support Code written by Michael D. Shah
// Author: Ruidi Huang
// Course: CS5850 Building Game Engines
// You can modify this could however you like in order to implement your 'pong'
//
// Last Updated: 01/17/23
// Please do not redistribute without asking permission.

#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
#else
	#include <SDL.h>
#endif

#include "GameModel.hpp"

int main(int argc, char* args[])
{
	// Create Game	
	GameModel model(1280, 1024);

	// Run Game
	model.Run();

	return 0;
}
