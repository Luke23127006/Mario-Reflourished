#include "Tile.h"

Tile::Tile(sf::Vector2f position) :
	Object(sf::Vector2f(50, 50), position)
{
}

Tile::Tile(sf::Vector2f position, sf::Texture& texture) : 
	Object(sf::Vector2f(50, 50), position)
{
	this->sprite.setTexture(texture);
	this->hitbox.setFillColor(sf::Color::Green);
	this->sprite.setScale(this->hitbox.getSize().x / texture.getSize().x, this->hitbox.getSize().y / texture.getSize().y);
}

Tile::~Tile()
{
}

const bool Tile::isHarming() const
{
	return this->harming;
}

const bool Tile::isShaking() const
{
	return this->shakeDuration > 0.f;
}

const bool Tile::isNeedUpdating() const
{
	return this->needUpdating;
}

void Tile::stopHarming()
{
	this->harming = false;
}

void Tile::shake()
{
	if (this->sprite.getTexture() != &Resources::textures["BRICK"]) return;
	this->shakeDuration = TILE_SHAKE_DURATION;
	this->harming = true;
	this->needUpdating = true;
}

void Tile::update(float deltaTime)
{
	this->shakeDuration = std::max(0.f, this->shakeDuration - deltaTime);
	if (this->shakeDuration == 0.f) this->needUpdating = false;
	this->harming = false;
}

void Tile::render(sf::RenderTarget& target)
{
	if (this->shakeDuration > 0.f)
	{
		float shakeStrength = 1000.f;
		this->sprite.setPosition(
			this->getPosition() + shakeStrength * sf::Vector2f(0.f, this->shakeDuration * this->shakeDuration - TILE_SHAKE_DURATION * this->shakeDuration));
	}
	else
	{
		this->sprite.setPosition(this->getPosition());
	}
	//target.draw(this->hitbox);
	target.draw(this->sprite);
}
