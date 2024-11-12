#pragma once

#include <SFML/Graphics.hpp>
#include "Global.h"

class Object
{
protected:
	sf::RectangleShape hitbox;
	//sf::Sprite sprite;
	
	bool enabled;

public:
	Object();
	Object(sf::Vector2f size, sf::Vector2f position);
	virtual ~Object();

	const sf::FloatRect getGLobalBounds() const;
	void setPosition(sf::Vector2f position);
	void setOrigin(sf::Vector2f origin);
	void setEnabled(bool enabled);

	virtual void update(float deltaTime);
	virtual void render(sf::RenderTarget& target);
};

