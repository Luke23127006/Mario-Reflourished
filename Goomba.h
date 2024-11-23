#pragma once
#include "Enemy.h"
#include "Resources.h"

class Goomba : public Enemy
{
public:
	Goomba();
	Goomba(sf::Vector2f size, sf::Vector2f position, int health);
	virtual ~Goomba();

	void takeDamage() override;
	void update(float deltaTime) override;
};

