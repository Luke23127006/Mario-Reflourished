#include "Lava.h"

Lava::Lava(sf::Vector2f position, bool isSurface) :
	Tile(position, Resources::textures["LAVA_BELOW"])
{
	this->danger = true;
	this->solid = false;
}

Lava::~Lava()
{
}
