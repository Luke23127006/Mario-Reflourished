#pragma once

#include "Object.h"
#include "Particle.h"
#include <vector>

class Tile : public Object
{
protected:
	bool canShake = false;
	bool danger = false;
	float shakeDuration = 0.f;
	bool harming = false;
	bool solid = true;
	bool breakable = false;
	float breakDuration = -1.f;

	std::vector<Particle*> particles;
public:
	Tile(sf::Vector2f position);
	Tile(sf::Vector2f position, sf::Texture& texture);
	Tile(sf::Vector2f position, sf::Texture& texture, bool canShake);
	Tile(sf::Vector2f position, sf::Texture& texture, bool canShake, bool breakable);
	virtual ~Tile();

	const bool isHarming() const;
	const bool isShaking() const;
	const bool isDanger() const;
	const bool isSolid() const;
	const bool isBreakable() const;
	const bool isBroken() const;
	virtual const bool isNeedUpdating() const;

	virtual void seftBreak();
	void stopHarming();
	virtual void shake();
	virtual void setShake(bool canShake);
	virtual void update(float deltaTime) override;

	virtual void render(sf::RenderTarget& target) override;
};

