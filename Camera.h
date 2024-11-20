#pragma once

#include <SFML/Graphics.hpp>
#include "Global.h"

class Camera
{
private:
	sf::Vector2f position;
	sf::Vector2f velocity;

public:
	Camera();
	virtual ~Camera();

	const sf::View getView(sf::Vector2u windowSize) const;
	void setPosition(sf::Vector2f position);
	void move(sf::Vector2f velocity);

	void update(float deltaTime, sf::Vector2f playerPosition);
	void update(float deltaTime, sf::Vector2f playerPosition, GameState gameState);
};