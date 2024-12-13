#include "SpikeWall.h"

SpikeWall::SpikeWall(sf::Vector2f position) :
	Object(sf::Vector2f(SPIKE_WALL_WIDTH, SPIKE_WALL_HEIGHT), position)
{
	this->hitbox.setFillColor(sf::Color(0, 183, 239, 64));
	this->sprite.setPosition(this->hitbox.getPosition());
	this->sprite.setTexture(Resources::textures["SPIKE_WALL"]);
}

void SpikeWall::move(sf::Vector2f velocity)
{
	this->hitbox.move(velocity);
	this->sprite.setPosition(this->hitbox.getPosition());
}