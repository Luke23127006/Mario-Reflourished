#include "Water.h"

Water::Water(sf::Vector2f position, bool isSurface) :
	Tile(position, Resources::textures["LUCKY_BLOCK"])
{
	this->solid = false;
}

Water::~Water()
{
}
