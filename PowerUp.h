#pragma once

#include "Entity.h"
#include "Global.h"
#include "Resources.h"

#include <SFML/Graphics.hpp>

class Player;

class PowerUp : public Entity
{
private:
	sf::FloatRect container;

protected:
	float duration;
public:
	PowerUp(sf::FloatRect container);
	virtual ~PowerUp();

	const float getDuration() const;
	void rise(float deltaTime);
	void turnAround();

	void collideWithTile(Tile* tile, Direction from) override;

	void collideWithEntity(Entity* entity, Direction& from) override;

	void update(float deltaTime) override;

	virtual void applyPowerUp(Player* player);
};