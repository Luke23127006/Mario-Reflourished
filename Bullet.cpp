#include "Bullet.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f velocity)
	: Entity(position, velocity), duration(2.0f)
{
	this->velocity = velocity;
}

Bullet::~Bullet()
{
}

void Bullet::bounce()
{
	this->velocity.y = -this->velocity.y;
}

bool Bullet::isExpired()
{
	return this->duration <= 0.0f;
}
