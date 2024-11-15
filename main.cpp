#include "Game.h"

int main()
{
	//Resources::Resources();
	//sf::Clock clock;

	//Game game;
	//while (game.running())
	//{
	//	float deltaTime = clock.restart().asSeconds();
	//	float FPS = 1.f / deltaTime;
	//	if (FPS < 30.f) continue;

	//	game.update(deltaTime);
	//	game.render();
	//}
	Game game;
	game.run();
	return 0;
}