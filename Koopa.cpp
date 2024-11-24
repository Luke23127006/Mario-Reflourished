#include "Koopa.h"

Koopa::Koopa(sf::Vector2f position)
	: Enemy(sf::Vector2f(KOOPA_WIDTH, KOOPA_HEIGHT), position)
{
	this->sprite.setTexture(Resources::textures["KOOPA"]);
	this->velocity = sf::Vector2f(KOOPA_MAX_SPEED, 0.f);
	this->hitbox.setFillColor(sf::Color(64, 128, 64, 255));
}

Koopa::~Koopa()
{
}

void Koopa::squished()
{
	Enemy::squished();
	this->dieTimer = 0.f;
}
