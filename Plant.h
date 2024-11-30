#pragma once

#include "Enemy.h"
#include "Animation.h"
#include "Resources.h"
#include "Global.h"

class Plant : public Enemy
{
private:
	PlantState state = PlantState::MOVING_UP;
	Animation* animation;
	float timer;
public:
	Plant();
	Plant(sf::Vector2f size, sf::Vector2f position);
	~Plant();

	void update(float deltaTime) override;
	void changeType();
	void takeDamage() override;
};

