#pragma once
#include "Entity.h"

class Enemy : public Entity
{
protected:
	int health;

	EnemyDieType dieType;
public:
	Enemy();
	Enemy(sf::Vector2f size, sf::Vector2f position);
	Enemy(sf::Vector2f size, sf::Vector2f position, int health);
	virtual ~Enemy();

	void turnAround();
	void die(EnemyDieType dieType);

	virtual void takeDamage();
	virtual void update(float deltaTime) override;
};

