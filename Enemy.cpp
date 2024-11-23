#include "Enemy.h"

Enemy::Enemy() : Entity(sf::Vector2f(50.f, 50.f), sf::Vector2f(0.f, 0.f))
{
	this->health = 100;
}

Enemy::Enemy(sf::Vector2f size, sf::Vector2f position, int health) : Entity(size, position)
{
	this->health = health;
}

Enemy::~Enemy()
{
}

void Enemy::takeDamage()
{
}

void Enemy::update(float deltaTime)
{
}