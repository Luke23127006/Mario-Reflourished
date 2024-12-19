#pragma once

#include "PowerUp.h"

class FireFlower : public PowerUp
{
public:
	FireFlower(Player* player);
	virtual ~FireFlower();
	void applyPowerUp(float deltaTime) override;
};

