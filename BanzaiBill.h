#pragma once

#include "Enemy.h"
#include "Resources.h"

class BanzaiBill : public Enemy
{
private:
	float timer;
public:
	BanzaiBill();
	BanzaiBill(sf::Vector2f size, sf::Vector2f position);
	~BanzaiBill();

	void update(float deltaTime) override;
	void takeDamage() override;
};

