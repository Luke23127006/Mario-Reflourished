#pragma once

#include "Resources.h"
#include "Tile.h"

class Pipe : public Tile
{
public:
	Pipe(sf::Vector2f position, PipeType type);
	virtual ~Pipe();
};

