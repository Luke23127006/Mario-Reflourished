#pragma once

#include "Enemy.h"
#include "Animation.h"
#include "Resources.h"





class Wukong : public Enemy
{
private:
	Animation* animation;
public:
	Wukong();
	Wukong(sf::Vector2f position);
	~Wukong();
	void collideWithEntity(Bullet* bullet, Direction from) override;
	void collideWithEntity(Shell* shell, Direction from) override;
	void collideWithTile(Lava* lava, Direction from) override;
	
};
