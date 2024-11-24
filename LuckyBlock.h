#pragma once

#include "Animation.h"
#include "Global.h"
#include "Particle.h"
#include "Resources.h"
#include "Tile.h"
#include "EntityFactory.h"

#include <ctime>

class LuckyBlock : public Tile
{
private:
	LuckyBlockType type;
	Particle* particle;

	bool activated;
	Animation* animation;

public:
	LuckyBlock(sf::Vector2f position, LuckyBlockType type);
	virtual ~LuckyBlock();

	const sf::Vector2f getCenter() const;
	const bool isActivated() const;
	const LuckyBlockType getType() const;
	void activate();
	PowerUp* launchPowerUp();

	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;
};

