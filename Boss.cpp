#include "Boss.h"

Boss::Boss() : Enemy(sf::Vector2f(100, 100), sf::Vector2f(0, 0), 100)
{
	this->sprite.setTexture(Resources::textures["BOSS"]);
}

Boss::Boss(sf::Vector2f size, sf::Vector2f position) : Enemy(size, position, 100)
{
	this->sprite.setTexture(Resources::textures["BOSS"]);
}

Boss::~Boss()
{
}

void Boss::attack()
{
}

void Boss::update(float deltaTime)
{
}

void Boss::takeDamage()
{
}