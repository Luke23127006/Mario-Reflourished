#pragma once

#include "Enemy.h"
#include "Animation.h"
#include "Resources.h"

class Plant : public Enemy
{
private:
	PlantState state = PlantState::MOVING_UP;
	Animation* animation;
	PlantType type = PlantType::GREEN;
	std::string typeString = "GREEN_PLANT";
	float timer;
public:
	Plant();
	Plant(sf::Vector2f size, sf::Vector2f position);
	~Plant();

	void update(float deltaTime) override;
	void changeType();
	void takeDamage() override;
};

