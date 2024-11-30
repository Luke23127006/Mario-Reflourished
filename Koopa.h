#pragma once

#include "Animation.h"
#include "Enemy.h"
#include "Resources.h"
#include "Global.h"

class Koopa : public Enemy
{
private:
	Animation* animation;
public:
	Koopa(sf::Vector2f position);
	~Koopa();

	void squished() override;
	void render(sf::RenderTarget& target) override;
};

