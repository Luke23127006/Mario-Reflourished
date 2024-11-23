#include "Enemy.h"

Enemy::Enemy() : 
	Entity(sf::Vector2f(50.f, 50.f), sf::Vector2f(0.f, 0.f)),
	health(1),
	dieType(EnemyDieType::SQUISH)
{
}

Enemy::Enemy(sf::Vector2f size, sf::Vector2f position) :
	Entity(size, position),
	health(1),
	dieType(EnemyDieType::SQUISH)
{
}

Enemy::Enemy(sf::Vector2f size, sf::Vector2f position, int health) : 
	Entity(size, position),
	health(health),
	dieType(EnemyDieType::SQUISH)
{
}

Enemy::~Enemy()
{
}

void Enemy::turnAround()
{
	this->velocity.x = -this->velocity.x;
}

void Enemy::die(EnemyDieType dieType)
{
	this->enabled = false;
	this->dying = true;
	this->dieType = dieType;
	if (this->dieType == EnemyDieType::SQUISH) this->dieTimer = ENEMY_DIE_TIME;
	else this->dieTimer = 3.f;
}

void Enemy::takeDamage()
{
}

void Enemy::update(float deltaTime)
{
	if (this->dying)
	{
		this->dieTimer = std::max(0.f, this->dieTimer - deltaTime);
	}
	else this->hitbox.move(this->velocity * deltaTime);
}