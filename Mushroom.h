#pragma once

#include "PowerUp.h"

class Mushroom : public PowerUp
{
public:
	Mushroom(sf::FloatRect container, Player* player);
	virtual ~Mushroom();

	void applyPowerUp() override;
};

