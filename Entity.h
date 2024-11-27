#pragma once

#include "Global.h"
#include "Object.h"

class Entity : public Object
{
private:
	sf::Vector2f lastPosition;

protected:
	sf::Vector2f velocity;

	bool onGround;
	bool flipped;
	float dieTimer;
	bool dying;

public:
	Entity(sf::Vector2f size, sf::Vector2f position);
	virtual ~Entity();

	const bool isDead() const;
	const bool isDying() const;

	void setOnGround(bool onGround);
	void setVelocity(sf::Vector2f velocity);
	void jump();

	sf::Vector2f getLastPosition();
	sf::Vector2f getVelocity();
	virtual void die();

	virtual void update(float deltaTime) override;
	void updateLastPosition();
};
