#pragma once
#include "Enemy.h"
#include "Resources.h"






class Bird : public Enemy
{
public:
	Bird(sf::Vector2f position);
	virtual ~Bird();

	void render(sf::RenderTarget& target) override;
};