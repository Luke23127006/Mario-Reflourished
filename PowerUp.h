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
	float duration = 0.f;
	float durationMax = 0.f;
	Player* player = nullptr;
	PowerUpType type = PowerUpType::NUM_POWER_UPS;
	sf::Sprite icon;

public:
	PowerUp(sf::FloatRect container);
	PowerUp(Player* player);
	virtual ~PowerUp();

	const float getDuration() const;
	void rise(float deltaTime);
	const PowerUpType getType() const;
	const sf::Sprite& getIcon() const;
	const bool isExpired() const;
	const float getDurationPercentage() const;
	void turnAround();
	void setInfinityDuration();
	void resetDuration();
	void expire();

	void collideWithTile(Tile* tile, Direction from) override;

	void collideWithEntity(Entity* entity, Direction& from) override;

	void update(float deltaTime) override;

	virtual void applyPowerUp(float deltaTime);
};