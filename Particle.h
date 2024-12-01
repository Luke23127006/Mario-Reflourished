#pragma once

#include "Decoration.h"

class Particle : public Decoration
{
private:
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float duration;

public:
	Particle(const sf::Texture& texture, sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration, float duration);
	virtual ~Particle();
	
	void setTextureRect(sf::IntRect textureRect);

	const bool isExpired() const;
	void update(float deltaTime);
};

