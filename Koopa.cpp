#include "Koopa.h"

Koopa::Koopa()
	: Enemy(sf::Vector2f(50.f, 50.f), sf::Vector2f(0.f, 0.f), 100)
{
	this->shell = Shell(this->getLastPosition(), sf::Vector2f(0.f, 0.f));
	this->sprite.setTexture(Resources::textures["KOOPA"]);
}

Koopa::Koopa(sf::Vector2f size, sf::Vector2f position, int health)
	: Enemy(size, position, health)
{
	this->shell = Shell(this->getLastPosition(), sf::Vector2f(0.f, 0.f));
	this->sprite.setTexture(Resources::textures["KOOPA"]);
}

Koopa::~Koopa()
{
}

void Koopa::update(float deltaTime)
{
}

void Koopa::dropShell()
{
	this->shell.setPosition(this->getLastPosition());
	this->shell.setVelocity(sf::Vector2f(0.f, 0.f));
}

void Koopa::takeDamage()
{
	this->health -= 50;
	if (this->health <= 0)
	{
		this->dropShell();
	}
}