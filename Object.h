#pragma once

#include "Global.h"
#include "Resources.h"

#include <SFML/Graphics.hpp>

class Object
{
protected:
	sf::RectangleShape hitbox;
	sf::Sprite sprite;
	
	bool enabled;

public:
	Object();
	Object(sf::Vector2f size, sf::Vector2f position);
	virtual ~Object();

	const bool getEnabled() const;
	sf::Vector2f getPosition() const;
	const sf::FloatRect getGLobalBounds() const;
	const sf::Vector2f getCenter() const;

	void setSize(sf::Vector2f size);
	void setPosition(sf::Vector2f position);
	void setOrigin(sf::Vector2f origin);
	void setEnabled(bool enabled);

	sf::FloatRect getGlobalBounds() const;

	virtual void update(float deltaTime);
	virtual void render(sf::RenderTarget& target);
};

