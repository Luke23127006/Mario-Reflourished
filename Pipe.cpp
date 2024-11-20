#include "Pipe.h"

Pipe::Pipe(sf::Vector2f position, PipeType type) :
	Tile(position)
{
	this->hitbox.setSize(sf::Vector2f(TILE_SIZE / 2, TILE_SIZE));
	if (type == PipeType::BOTTOM_LEFT)
	{
		this->sprite.setTexture(Resources::textures["PIPE_BOTTOM_LEFT"]);
	}
	else if (type == PipeType::BOTTOM_RIGHT)
	{
		this->sprite.setTexture(Resources::textures["PIPE_BOTTOM_RIGHT"]);
		this->hitbox.setOrigin(sf::Vector2f(-TILE_SIZE / 2, 0));
	}
	else if (type == PipeType::TOP_LEFT)
	{
		this->sprite.setTexture(Resources::textures["PIPE_TOP_LEFT"]);
	}
	else if (type == PipeType::TOP_RIGHT)
	{
		this->sprite.setTexture(Resources::textures["PIPE_TOP_RIGHT"]);
		this->hitbox.setOrigin(sf::Vector2f(-TILE_SIZE / 2, 0));
	}
}

Pipe::~Pipe()
{
}
