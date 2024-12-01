#include "Goomba.h"
#include <iostream>

Goomba::Goomba(sf::Vector2f position)
	: Enemy(sf::Vector2f(GOOMBA_WIDTH, GOOMBA_HEIGHT), position)
{
	this->velocity = sf::Vector2f(GOOMBA_MAX_SPEED, 0.f);
	this->hitbox.setFillColor(sf::Color(255, 128, 0, 255));
	this->hitbox.setSize(sf::Vector2f(GOOMBA_WIDTH, GOOMBA_HEIGHT));
	this->hitbox.setPosition(position);
	animation = new Animation(Resources::textures["GOOMBA"], 2, 0.08f, sf::Vector2i(GOOMBA_WIDTH, GOOMBA_HEIGHT));
}

Goomba::~Goomba()
{
	delete this->animation;
}

void Goomba::render(sf::RenderTarget& target)
{
	this->animation->render(target, this->getPosition());
	target.draw(this->hitbox);
}