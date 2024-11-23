#pragma once
#include "Enemy.h"
#include "Resources.h"
#include "Animation.h"

class Goomba : public Enemy
{
private:
	Animation* animation;
public:
	Goomba(sf::Vector2f position);
	virtual ~Goomba();
};

