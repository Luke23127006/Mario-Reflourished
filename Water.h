#pragma once
#include "Tile.h"

class Water : public Tile
{
public:
	Water(sf::Vector2f position, bool isSurface);
	~Water();
};

