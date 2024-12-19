#pragma once

#include "PowerUp.h"

class Magnet : public PowerUp
{
public:
	Magnet(Player* player);
	virtual ~Magnet();
	void applyPowerUp(float deltaTime) override;
};

