#pragma once

#include "Enemy.h"
#include "Resources.h"

class Koopa : public Enemy
{
public:
	Koopa(sf::Vector2f position);
	~Koopa();

	void squished() override;
};

