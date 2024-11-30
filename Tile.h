#pragma once

#include "Object.h"

class Tile : public Object
{
protected:
	bool canShake = false;
	bool danger = false;
	float shakeDuration = 0.f;
	bool harming = false;
	bool solid = true;
public:
	Tile(sf::Vector2f position);
	Tile(sf::Vector2f position, sf::Texture& texture);
	Tile(sf::Vector2f position, sf::Texture& texture, bool canShake);
	virtual ~Tile();

	const bool isHarming() const;
	const bool isShaking() const;
	const bool isDanger() const;
	const bool isSolid() const;
	virtual const bool isNeedUpdating() const;
	void stopHarming();
	virtual void shake();

	virtual void update(float deltaTime) override;

	virtual void render(sf::RenderTarget& target) override;
};

