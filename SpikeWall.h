#pragma once

#include "Object.h"

class SpikeWall : public Object
{
public:
	SpikeWall(sf::Vector2f position);

	void move(sf::Vector2f velocity);
};

