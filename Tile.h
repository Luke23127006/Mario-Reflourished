#pragma once

#include "Object.h"

class Tile : public Object
{
public:
	Tile(sf::Vector2f position);
	Tile(sf::Vector2f position, const sf::Texture& texture);
	virtual ~Tile();

	virtual void update(float deltaTime) override;

	virtual void render(sf::RenderTarget& target) override;
};

