#include "Tile.h"

Tile::Tile(sf::Vector2f position) :
	Object(sf::Vector2f(TILE_SIZE, TILE_SIZE), position),
	canShake(false)
{
}

Tile::Tile(sf::Vector2f position, sf::Texture& texture) : 
	Object(sf::Vector2f(50, 50), position),
	canShake(false)
{
	this->sprite.setTexture(texture);
	this->hitbox.setFillColor(sf::Color::Green);
	this->sprite.setScale(this->hitbox.getSize().x / texture.getSize().x, this->hitbox.getSize().y / texture.getSize().y);
}

Tile::Tile(sf::Vector2f position, sf::Texture& texture, bool canShake) :
	Object(sf::Vector2f(50, 50), position),
	canShake(canShake)
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

const bool Tile::isDanger() const
{
	return this->danger;
}

const bool Tile::isSolid() const
{
	return this->solid;
}

const bool Tile::isNeedUpdating() const
{
	return this->shakeDuration > 0.f;
}

void Tile::stopHarming()
{
	this->harming = false;
}

void Tile::shake()
{
	if (!this->canShake) return;
	this->shakeDuration = TILE_SHAKE_DURATION;
	this->harming = true;
}

void Tile::update(float deltaTime)
{
	this->shakeDuration = std::max(0.f, this->shakeDuration - deltaTime);
	this->harming = false;

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
}

void Tile::render(sf::RenderTarget& target)
{
	//target.draw(this->hitbox);
	target.draw(this->sprite);
}
