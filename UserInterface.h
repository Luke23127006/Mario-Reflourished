#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include<vector>
#include "Global.h"
#include "Resources.h"




class Scene
{
public:
	virtual ~Scene() = default;
	virtual void update(float deltaTime);                     // Pure virtual
	virtual void render(sf::RenderWindow& window) = 0;     // Pure virtual
	virtual GameState getNextScene() = 0;                  // Pure virtual
};







