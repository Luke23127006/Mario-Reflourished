#include "Koopa.h"

Koopa::Koopa(sf::Vector2f position)
	: Enemy(sf::Vector2f(KOOPA_WIDTH, KOOPA_HEIGHT), position)
{
	this->velocity = sf::Vector2f(KOOPA_PACE_SPEED, 0.f);

	this->hitbox.setFillColor(sf::Color(64, 128, 64, 128));
	this->hitbox.setSize(sf::Vector2f(KOOPA_WIDTH, KOOPA_HEIGHT));
	this->hitbox.setPosition(position);

	this->animations.push_back(new Animation(Resources::textures["KOOPA"], 2, 0.2f, sf::Vector2i(KOOPA_WIDTH, KOOPA_HEIGHT)));
}

Koopa::~Koopa()	
{
}

void Koopa::squished()
{
	Enemy::squished();
	this->dieTimer = 0.f;
	this->addEntity(new Shell(this->getPosition()));
}