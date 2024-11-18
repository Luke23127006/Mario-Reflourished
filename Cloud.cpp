#include "Cloud.h"

Cloud::Cloud(sf::Vector2f velocity)
	: Decoration(Resources::textures["CLOUD"])
{
	this->velocity = velocity;
}

Cloud::~Cloud()
{
}

void Cloud::update(float deltaTime)
{
	this->sprite.move(this->velocity * deltaTime);
}