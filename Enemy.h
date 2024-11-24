#pragma once

#include "Entity.h"

class Enemy : public Entity
{
protected:
	int health;
	bool isSquished = false;
public:
	Enemy();
	Enemy(sf::Vector2f size, sf::Vector2f position);
	Enemy(sf::Vector2f size, sf::Vector2f position, int health);
	virtual ~Enemy();

	void turnAround();
	virtual void die() override;
	virtual void squished();

	virtual void takeDamage();
	virtual void update(float deltaTime) override;
};

