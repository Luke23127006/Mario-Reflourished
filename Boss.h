#pragma once

#include "Enemy.h"
#include "Animation.h"
#include "Resources.h"

class Boss : public Enemy
{
private:
	Animation* animation;
public:
	Boss();
	Boss(sf::Vector2f size, sf::Vector2f position);
	~Boss();

	void attack();
	void update(float deltaTime) override;
	void takeDamage() override;
};

