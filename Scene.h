#pragma once

#include "Button.h"
#include "Global.h"
#include "Resources.h"
#include <math.h>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

class Scene
{
protected:

	std::vector<Button*> buttons;
	int selectedButton;
	bool isPressedUp;
	bool isPressedDown;
	ControlMode currentControlMode;


public:
	Scene();
	virtual ~Scene() = default;
	void updateKeyBoardControl();
	void updateMouseControl();
	void colorButton();
	virtual void updateClickButton(bool& held);
	virtual void updateHoverButton();
	virtual void draw(sf::RenderWindow& window);
	virtual void update(float deltaTime, bool& held);
	virtual void render(sf::RenderWindow& window) = 0;   // Pure virtual
	virtual GameState getNextScene() = 0;                  // Pure virtual
};







