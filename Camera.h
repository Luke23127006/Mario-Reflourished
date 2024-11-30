#pragma once

#include "Global.h"

#include <SFML/Graphics.hpp>

class Camera
{
private:
	sf::Vector2f position;
	sf::Vector2f velocity;

public:
	Camera();
	virtual ~Camera();

	const sf::View getView(sf::Vector2u windowSize) const;
	const sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f position);
	void move(sf::Vector2f velocity);

	void update(float deltaTime, sf::Vector2f playerPosition);
};