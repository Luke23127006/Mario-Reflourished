#pragma once

#include "Object.h"

class Tile : public Object
{
protected:
	bool canShake = false;
	float shakeDuration = 0.f;
	bool harming = false;
public:
	Tile(sf::Vector2f position);
	Tile(sf::Vector2f position, sf::Texture& texture);
	Tile(sf::Vector2f position, sf::Texture& texture, bool canShake);
	virtual ~Tile();

	const bool isHarming() const;
	const bool isShaking() const;
	virtual const bool isNeedUpdating() const;
	void stopHarming();
	virtual void shake();

	virtual void update(float deltaTime) override;

	virtual void render(sf::RenderTarget& target) override;
};

