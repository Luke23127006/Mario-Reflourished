#pragma once

#include "Enemy.h"
#include "Animation.h"
#include "Resources.h"

class BanzaiBill : public Enemy
{
private:
	float timer;
	Animation* animation;
public:
	BanzaiBill();
	BanzaiBill(sf::Vector2f size, sf::Vector2f position);
	~BanzaiBill();

	void update(float deltaTime) override;
	void takeDamage() override;
	void render(sf::RenderTarget& target) override;
};

