#pragma once

#include "Animation.h"
#include "Object.h"
#include "Resources.h"

class Coin : public Object
{
private:
	Animation* animation;

public:
	Coin(sf::Vector2f position);
	virtual ~Coin();

	const bool isCollected() const;
	void move(sf::Vector2f velocity, float deltaTime);

	void update(float deltaTime) override;
	void collected();
	void render(sf::RenderTarget& target) override;
};
