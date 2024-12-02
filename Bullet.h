#pragma once

#include "Entity.h"

class Bullet : public Entity
{
private:
	float duration;
	float angle;
public:
	Bullet(sf::Vector2f position, sf::Vector2f velocity);
	virtual ~Bullet();

	void bounce();
	bool isExpired();

	void update(float deltaTime) override;

	void render(sf::RenderTarget& target) override;
};

