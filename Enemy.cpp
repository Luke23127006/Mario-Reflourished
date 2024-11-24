#include "Enemy.h"
#include <iostream>

Enemy::Enemy() :
	Entity(sf::Vector2f(50.f, 50.f), sf::Vector2f(0.f, 0.f)),
	health(1)
{
}

Enemy::Enemy(sf::Vector2f size, sf::Vector2f position) :
	Entity(size, position),
	health(1)
{
}

Enemy::Enemy(sf::Vector2f size, sf::Vector2f position, int health) :
	Entity(size, position),
	health(health)
{
}

Enemy::~Enemy()
{
}

void Enemy::turnAround()
{
	this->velocity.x = -this->velocity.x;
}

void Enemy::die()
{
	this->enabled = false;
	this->dying = true;
	this->dieTimer = ENEMY_DIE_TIME;
	this->velocity = sf::Vector2f(0.f, -ENEMY_DIE_VELOCITY);
}

void Enemy::squished()
{
	this->isSquished = true;
	this->enabled = false;
	this->dying = true;
	this->dieTimer = ENEMY_SQUISHED_TIME;
	this->velocity = sf::Vector2f(0.f, 0.f);
}

void Enemy::takeDamage()
{
}

void Enemy::update(float deltaTime)
{
	if (this->dying)
	{
		this->dieTimer = std::max(0.f, this->dieTimer - deltaTime);
		if (!this->isSquished)
		{
			this->velocity.y += GRAVITY * deltaTime;
			this->hitbox.move(this->velocity * deltaTime);
		}
	}
	else this->hitbox.move(this->velocity * deltaTime);
}