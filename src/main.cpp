#include <iostream>
#include "game.h"
#include <windows.h>

int main(int argc, char* argv[])
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	Game* game = new Game();
	game->run();

	return 0;
}