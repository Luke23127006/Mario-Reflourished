#pragma once

#include "PowerUp.h"

class Mushroom : public PowerUp
{
public:
	Mushroom(Player* player);
	virtual ~Mushroom();

	void applyPowerUp(float deltaTime) override;
};

