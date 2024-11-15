#pragma once
#include "Resources.h"
#include "Global.h"
#include <SFML/Graphics.hpp>

class Decoration
{
protected:
    sf::Sprite sprite;

public:
    Decoration(sf::Texture& texture);
	virtual ~Decoration();

    void render(sf::RenderTarget& target); 
};
