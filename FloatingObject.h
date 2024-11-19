#pragma once

#include "Decoration.h"
#include "Resources.h"

class FloatingObject : public Decoration
{
private:
	float velocity;
	float expirationTime;
public:
	FloatingObject(const sf::Texture& texture, sf::Vector2f position);
	virtual ~FloatingObject();

	const bool isExpired() const;

	void update(float deltaTime);
	void render(sf::RenderTarget& target);
};

