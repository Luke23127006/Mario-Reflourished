#pragma once

#include "Resources.h"
#include "Tile.h"
#include "Animation.h"
#include "Global.h"
#include <ctime>

class LuckyBlock : public Tile
{
private:
	LuckyBlockType type;
	PowerUpType powerUpType;

	bool activated;
	Animation* animation;

public:
	LuckyBlock(sf::Vector2f position, LuckyBlockType type);
	LuckyBlock(sf::Vector2f position, LuckyBlockType type, PowerUpType powerUpType);
	virtual ~LuckyBlock();

	void activate();
	PowerUpType getPowerUpType();

	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;
};

