#include "Goomba.h"
#include <iostream>

Goomba::Goomba(sf::Vector2f position)
	: Enemy(sf::Vector2f(GOOMBA_WIDTH, GOOMBA_HEIGHT), position)
{
	this->sprite.setTexture(Resources::textures["GOOMBA"]);
	this->velocity = sf::Vector2f(GOOMBA_PACE_SPEED, 0.f);
	this->hitbox.setFillColor(sf::Color(255, 128, 0, 128));
	this->hitbox.setSize(sf::Vector2f(GOOMBA_WIDTH, GOOMBA_HEIGHT));
	this->hitbox.setPosition(position);

	this->animations.push_back(new Animation(Resources::textures["GOOMBA"], 2, 0.2f, sf::Vector2i(GOOMBA_WIDTH, GOOMBA_HEIGHT)));
}

Goomba::~Goomba()
{
}