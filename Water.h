#pragma once
#include "Tile.h"
#include "Animation.h"

class Water : public Tile
{
private:
	Animation* animation;
public:
	Water(sf::Vector2f position, bool isSurface);
	~Water();

	const bool isNeedUpdating() const override;

	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;
};

