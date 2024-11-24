#include "Game.h"

int main()
{
	srand(time(NULL));
	Resources::initResources();
	ColorManager::initColors();
	Game game;
	game.run();


	return 0;
}