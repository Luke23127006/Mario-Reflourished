#include "Goomba.h"
#include <iostream>

Goomba::Goomba(sf::Vector2f position)
	: Enemy(sf::Vector2f(GOOMBA_WIDTH, GOOMBA_HEIGHT), position),
	animation(nullptr)
{
	this->sprite.setTexture(Resources::textures["GOOMBA"]);
	this->velocity = sf::Vector2f(GOOMBA_MAX_SPEED, 0.f);
	this->hitbox.setFillColor(sf::Color::Blue);
	this->hitbox.setSize(sf::Vector2f(50.f, 50.f));
	this->hitbox.setPosition(position);
}

Goomba::~Goomba()
{
}

void Goomba::takeDamage()
{
}

void Goomba::update(float deltaTime)
{
	this->hitbox.move(this->velocity * deltaTime);
}

void Goomba::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
