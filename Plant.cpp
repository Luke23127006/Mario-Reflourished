#include "Plant.h"

Plant::Plant() : Enemy(sf::Vector2f(32, 64), sf::Vector2f(0, 0), 1)
{
	this->sprite.setTexture(Resources::textures["PLANT"]);
	timer = 1.0;
}

Plant::Plant(sf::Vector2f size, sf::Vector2f position) : Enemy(size, position, 1)
{
	this->sprite.setTexture(Resources::textures["PLANT"]);
	timer = 1.0;
}

Plant::~Plant()
{
}

void Plant::update(float deltaTime)
{
}

void Plant::takeDamage()
{
}