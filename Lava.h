#pragma once

#include "Tile.h"

class Lava : public Tile
{
private:
public:
	Lava(sf::Vector2f position, bool isSurface);
	~Lava();
};

