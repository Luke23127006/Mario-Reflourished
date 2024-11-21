#include "Goomba.h"

Goomba::Goomba()
	: Enemy(sf::Vector2f(50.f, 50.f), sf::Vector2f(0.f, 0.f), 100)
{
	this->sprite.setTexture(Resources::textures["GOOMBA"]);
}

Goomba::Goomba(sf::Vector2f size, sf::Vector2f position, int health)
	: Enemy(size, position, health)
{
	this->sprite.setTexture(Resources::textures["GOOMBA"]);
}

Goomba::~Goomba()
{
}

void Goomba::takeDamage()
{
}

void Goomba::update(float deltaTime)
{
}