#pragma once

#include "Entity.h"

class Bullet : public Entity
{
private:
	float duration;
public:
	Bullet(sf::Vector2f position, sf::Vector2f velocity);
	virtual ~Bullet();

	void bounce();
	bool isExpired();

	void update(float deltaTime) override;
};

