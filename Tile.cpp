#include "Tile.h"

Tile::Tile(sf::Vector2f position) :
	Object(sf::Vector2f(50, 50), position)
{
}

Tile::Tile(sf::Vector2f position, const sf::Texture& texture) : 
	Object(sf::Vector2f(50, 50), position)
{
	//this->sprite.setTexture(texture);
	this->hitbox.setFillColor(sf::Color::Green);
}

Tile::~Tile()
{
}

void Tile::update(float deltaTime)
{
}

void Tile::render(sf::RenderTarget& target)
{
	//target.draw(this->sprite);
	target.draw(this->hitbox);
}
