#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include<vector>
#include "Global.h"
#include "Resources.h"




class Scene
{
protected:
	float debounceTime = 0.3f;
public:
	virtual ~Scene() = default;
	virtual void update(float dt);                     // Pure virtual
	virtual void render(sf::RenderWindow& window, float dt) = 0;     // Pure virtual
	virtual GameState getNextScene() = 0;                  // Pure virtual
};







