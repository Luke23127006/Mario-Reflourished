#pragma once

#include "Tile.h"
#include "Resources.h"

class Portal : public Tile
{
private:
	sf::Vector2f destination;

public:
	Portal(sf::Vector2f position, sf::Vector2f destination);
	~Portal();
};

