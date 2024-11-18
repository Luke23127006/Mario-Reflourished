#pragma once

#include "Resources.h"
#include "Object.h"
#include "Animation.h"

class Coin : public Object
{
private:
	Animation* animation;

public:
	Coin(sf::Vector2f position);
	virtual ~Coin();

	void update(float deltaTime) override;
};
