#include "Coin.h"

Coin::Coin(sf::Vector2f position)
{
	this->hitbox.setSize(sf::Vector2f(COIN_WIDTH, COIN_HEIGHT));
	this->hitbox.setPosition(position);
	this->hitbox.setFillColor(sf::Color(255, 235, 59, 128));

	this->animation = new Animation(Resources::textures["COIN"], 6, 0.1f, sf::Vector2i(16, 16));
	this->animation->setSize(this->hitbox.getSize());
    this->animation->setPosition(position);
}

Coin::~Coin()
{
    delete this->animation;
}

const bool Coin::isCollected() const
{
	return !this->enabled;
}

void Coin::move(sf::Vector2f velocity, float deltaTime)
{
	this->hitbox.move(velocity * deltaTime);
}

void Coin::update(float deltaTime)
{
	this->animation->update(deltaTime, false);
}

void Coin::collected()
{
	this->enabled = false;
	COINS++;
}

void Coin::render(sf::RenderTarget& target)
{
	Object::render(target);
	this->animation->render(target, this->hitbox.getPosition());
}