#include "Lava.h"

Lava::Lava(sf::Vector2f position, bool isSurface) :
	Tile(position, Resources::textures["LAVA_BELOW"])
{
	if (isSurface)
	{
		this->sprite.setTexture(Resources::textures["LAVA_SURFACE"]);
	}
	this->danger = true;
	this->solid = false;
}

Lava::~Lava()
{
}
