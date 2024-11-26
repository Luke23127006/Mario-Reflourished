#pragma once

#include "Object.h"

class Tile : public Object
{
protected:
	float shakeDuration = 0.f;
	bool harming = false;
	bool needUpdating = false;
public:
	Tile(sf::Vector2f position);
	Tile(sf::Vector2f position, sf::Texture& texture);
	virtual ~Tile();

	const bool isHarming() const;
	const bool isShaking() const;
	const bool isNeedUpdating() const;
	void stopHarming();
	void shake();

	virtual void update(float deltaTime) override;

	virtual void render(sf::RenderTarget& target) override;
};

