#pragma once

#include "Resources.h"
#include "Tile.h"

class Portal : public Tile
{
private:
	sf::Vector2f destination;

public:
	Portal(sf::Vector2f position, sf::Vector2f destination);
	~Portal();

	const sf::Vector2f getDestination() const;
};

