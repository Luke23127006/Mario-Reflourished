#pragma once

#include "Animation.h"
#include "Enemy.h"
#include "Resources.h"

class Goomba : public Enemy
{
private:
public:
	Goomba(sf::Vector2f position);
	virtual ~Goomba();

	void render(sf::RenderTarget& target) override;
};

