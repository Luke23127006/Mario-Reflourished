#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Global.h"
#include "Resources.h"

class PowerUp : public Entity
{
private:
	PowerUpType type;
	float duration;
	sf::FloatRect container;

public:
	PowerUp(PowerUpType type, sf::FloatRect container);
	virtual ~PowerUp();

	PowerUpType getType();
	void rise(float deltaTime);

	void update(float deltaTime) override;
};