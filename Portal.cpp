#include "Portal.h"

Portal::Portal(sf::Vector2f position, sf::Vector2f destination) :
	Tile(position, Resources::textures["PIPE_BOTTOM_LEFT"]),
	destination(destination)
{
	this->hitbox.setSize(sf::Vector2f(TILE_SIZE + TILE_SIZE * 0.5f, TILE_SIZE * 0.5f));
	this->hitbox.setOrigin(sf::Vector2f(0.f, -TILE_SIZE * 0.5f));
}

Portal::~Portal()
{
}

const sf::Vector2f Portal::getDestination() const
{
	return this->destination;
}
