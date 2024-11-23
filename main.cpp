#include "Game.h"

int main()
{
	Resources::initResources();
	ColorManager::initColors();
	Game game;
	game.run();


	return 0;
}