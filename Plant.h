#pragma once

#include "Enemy.h"
#include "Resources.h"

class Plant : public Enemy
{
private:
	PlantState state = PlantState::MOVING_UP;
	float timer;
public:
	Plant();
	Plant(sf::Vector2f size, sf::Vector2f position);
	~Plant();

	void update(float deltaTime) override;
	void takeDamage() override;
};

