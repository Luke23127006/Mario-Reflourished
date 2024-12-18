#pragma once

#include "PowerUp.h"

class Shield : public PowerUp
{
public:
	Shield(Player* player);
	virtual ~Shield();
	void applyPowerUp() override;
};

