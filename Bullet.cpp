#include "Bullet.h"
#include <iostream>

Bullet::Bullet(sf::Vector2f position, sf::Vector2f velocity)
	: Entity(sf::Vector2f(BULLET_WIDTH, BULLET_HEIGHT), position), 
	duration(2.0f)
{
	this->velocity = velocity;
	this->hitbox.setSize(sf::Vector2f(10, 10));
}

Bullet::~Bullet()
{
}

void Bullet::bounce()
{
	this->velocity.y = -500.f;
}

bool Bullet::isExpired()
{
	return this->duration <= 0.f;
}

void Bullet::update(float deltaTime)
{
	if (!this->dying)
	{
		this->duration -= deltaTime;
		if (this->duration <= 0.f) this->die();
		this->velocity.y += GRAVITY * deltaTime;
		this->hitbox.move(this->velocity * deltaTime);
	}
}