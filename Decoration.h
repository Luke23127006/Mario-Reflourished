#pragma once

#include "Global.h"
#include "Resources.h"
#include "Animation.h"

#include <SFML/Graphics.hpp>

class Decoration
{
protected:
    sf::Sprite sprite;
	Animation* animation = nullptr;


public:
    Decoration(const sf::Texture& texture);
	Decoration(const sf::Texture& texture, sf::Vector2f position);
	Decoration(Animation* animation, sf::Vector2f position);
	virtual ~Decoration();

	void setScale(sf::Vector2f scale);
	void setCenter();

	void update(float deltaTime);

    void render(sf::RenderTarget& target); 
	void render(sf::RenderTarget& target, sf::Vector2f position);
};
