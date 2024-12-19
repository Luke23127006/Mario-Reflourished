#pragma once

#include "PowerUp.h"

class AirSneakers : public PowerUp
{
public:
	AirSneakers(Player* player);
	virtual ~AirSneakers();
	void applyPowerUp(float deltaTime) override;
};

