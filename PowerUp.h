#pragma once

#include "Entity.h"
#include "Global.h"
#include "Resources.h"

#include <SFML/Graphics.hpp>

class PowerUp : public Entity
{
private:
	PowerUpType type;
	
	sf::FloatRect container;
protected:
	float duration;
public:
	PowerUp(PowerUpType type, sf::FloatRect container);
	virtual ~PowerUp();

	PowerUpType getType();
	const float getDuration() const;
	void rise(float deltaTime);
	void turnAround();

	void collisionTile(Tile* tile, Direction from) override;

	void update(float deltaTime) override;
};