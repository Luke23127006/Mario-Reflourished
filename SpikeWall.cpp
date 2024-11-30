#include "SpikeWall.h"

SpikeWall::SpikeWall(sf::Vector2f position) :
	Object(sf::Vector2f(TILE_SIZE, 1.55f * SCREEN_HEIGHT), position)
{
}

void SpikeWall::move(sf::Vector2f velocity)
{
	this->hitbox.move(velocity);
}