#pragma once

#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Object.h"

class Entity : public Object
{
protected:
	sf::Vector2f lastPosition;
	sf::Vector2f velocity;

	bool onGround;
	bool flipped;
	bool dead;

public:
	Entity(sf::Vector2f size, sf::Vector2f position);
	virtual ~Entity();

	void setOnGround(bool onGround);
	virtual void die();

	virtual void update(float deltaTime) override;
};
