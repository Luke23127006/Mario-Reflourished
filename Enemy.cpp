#include "Enemy.h"

Enemy::Enemy() : 
	Entity(sf::Vector2f(50.f, 50.f), sf::Vector2f(0.f, 0.f))
{
	this->health = 1;
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

void Enemy::takeDamage()
{
}

void Enemy::update(float deltaTime)
{
	this->hitbox.move(this->velocity * deltaTime);
}