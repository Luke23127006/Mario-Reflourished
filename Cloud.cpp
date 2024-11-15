#include "Cloud.h"

Cloud::Cloud(sf::Vector2f velocity)
	: Decoration(Resources::textures["CLOUD"])
{
	this->velocity = velocity;
}

Cloud::~Cloud()
{
}
