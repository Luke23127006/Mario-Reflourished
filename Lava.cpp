#include "Lava.h"

Lava::Lava(sf::Vector2f position, bool isSurface) :
	Tile(position, Resources::textures["LUCKY_BLOCK"])
{
	this->danger = true;
	this->solid = false;
}

Lava::~Lava()
{
}
