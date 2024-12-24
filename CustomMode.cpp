#include "CustomMode.h"

CustomMode::CustomMode()
{
	//this->map = new Map(MAPS_DIRECTORY + "Custom/Empty.png", sf::Vector2f(0, 0));

	this->player = new Player(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT), sf::Vector2f(100, 0));

	//this->entities.push_back(this->player);
}

CustomMode::~CustomMode()
{
	//delete this->map;
	delete this->player;
}

void CustomMode::update(float deltaTime)
{
	this->player->update(deltaTime);
	//this->map->update(deltaTime, this->entities);

	//this->camera.update(deltaTime, this->player->getPosition());

	//Collision::handle_entity_map(this->player, this->map);
}

void CustomMode::render(sf::RenderWindow& window)
{
	//this->map->render(window);
	this->player->render(window);
}

GameState CustomMode::getNextScene()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		return GameState::PAUSE;
	return GameState::CUSTOM_MODE;
}
