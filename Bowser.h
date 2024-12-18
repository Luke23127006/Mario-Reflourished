#pragma once

#include "Enemy.h"
#include "Animation.h"
#include "Resources.h"

class Bowser : public Enemy
{
private:
	Animation* animation;
public:

	Bowser(sf::Vector2f position);

	~Bowser();
	
	void collideWithEntity(Bullet* bullet, Direction from) override;
	void collideWithEntity(Shell* shell, Direction from) override;
};

