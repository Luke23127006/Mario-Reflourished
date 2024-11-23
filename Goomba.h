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

	void takeDamage() override;
	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;
};

