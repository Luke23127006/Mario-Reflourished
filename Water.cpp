#include "Water.h"

Water::Water(sf::Vector2f position, bool isSurface) :
	Tile(position, Resources::textures["WATER_BELOW"])
{
	if (isSurface)
	{
		this->sprite.setTexture(Resources::textures["WATER_SURFACE"]);
	}
	this->solid = false;
}

Water::~Water()
{
}
