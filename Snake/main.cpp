#include "FileInclude.h"
#include "Game.h"

int main()
{
	srand((unsigned int)time(nullptr));

	Game game;
	game.Start();

	closegraph();
	return 0;
}

