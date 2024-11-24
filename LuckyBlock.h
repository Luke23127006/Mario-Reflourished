#pragma once

#include "Resources.h"
#include "Tile.h"
#include "Animation.h"
#include "Global.h"
#include "Particle.h"
#include "PowerUp.h"
#include <ctime>

class LuckyBlock : public Tile
{
private:
	LuckyBlockType type;
	Particle* particle;
	PowerUp* powerUp;

	bool activated;
	Animation* animation;

public:
	LuckyBlock(sf::Vector2f position);
	LuckyBlock(sf::Vector2f position, PowerUpType powerUpType);
	virtual ~LuckyBlock();

	const sf::Vector2f getCenter() const;
	void activate();
	PowerUp* getPowerUp();
	void removePowerUp();

	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;
};

