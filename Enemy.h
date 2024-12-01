#pragma once

#include "Entity.h"
#include "Animation.h"

class Enemy : public Entity
{
protected:
	int health;
	bool isSquished = false;
	std::vector<Animation*> animations;
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

