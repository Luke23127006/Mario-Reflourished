#pragma once

#include "Global.h"
#include "Resources.h"

#include <SFML/Graphics.hpp>

class Decoration
{
protected:
    sf::Sprite sprite;

public:
    Decoration(const sf::Texture& texture);
	Decoration(const sf::Texture& texture, sf::Vector2f position);
	virtual ~Decoration();

	void setScale(sf::Vector2f scale);

    void render(sf::RenderTarget& target); 
};
