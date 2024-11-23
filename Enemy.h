#pragma once
#include "Entity.h"

class Enemy : public Entity
{
protected:
	int health;
public:
	Enemy();
	Enemy(sf::Vector2f size, sf::Vector2f position, int health);
	virtual ~Enemy();

	virtual void takeDamage();
	virtual void update(float deltaTime) override;
};

