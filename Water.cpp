#include "Water.h"

Water::Water(sf::Vector2f position, bool isSurface) :
	Tile(position, Resources::textures["WATER_BELOW"])
{
	this->solid = false;
}

Water::~Water()
{
}
