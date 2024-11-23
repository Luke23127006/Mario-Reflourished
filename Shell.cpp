#include "Shell.h"

Shell::Shell() : Entity(sf::Vector2f(50.f, 50.f), sf::Vector2f(0.f, 0.f))
{
	this->sprite.setTexture(Resources::textures["SHELL"]);
}

Shell::Shell(sf::Vector2f size, sf::Vector2f position) : Entity(size, position)
{
	this->sprite.setTexture(Resources::textures["SHELL"]);
}

Shell::~Shell()
{
}

void Shell::update(float deltaTime)
{
}