#pragma once

#include "Tile.h"
#include "Resources.h"

class Pipe : public Tile
{
public:
	Pipe(sf::Vector2f position, PipeType type);
	virtual ~Pipe();
};

