#define SDL_MAIN_HANDLED
#include "VersusPhysicsGame.h"


bool running = true;

int main(int argc, char* args[])
{
	{
		VersusPhysicsGame Game;
		Game.Setup();
		Game.Start();
	}
	return 0;
}