#include "Coin.h"

Coin::Coin(sf::Vector2f position)
{
	this->hitbox.setSize(sf::Vector2f(16, 16));
	this->hitbox.setPosition(position);
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->animation = new Animation(Resources::textures["COIN"], 6, 0.08f, sf::Vector2i(16, 16));
    this->animation->setPosition(position);
}

Coin::~Coin()
{
    delete this->animation;
}

void Coin::update(float deltaTime)
{
}

void Coin::collected()
{
	this->enabled = false;
}

void Coin::render(sf::RenderTarget& target)
{
	this->animation->render(target, this->hitbox.getPosition());
	target.draw(this->hitbox);
}