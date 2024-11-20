#include "Portal.h"

Portal::Portal(sf::Vector2f position, sf::Vector2f destination) :
	Object(sf::Vector2f(TILE_SIZE, TILE_SIZE), position),
	destination(destination)
{
}

Portal::~Portal()
{
}
