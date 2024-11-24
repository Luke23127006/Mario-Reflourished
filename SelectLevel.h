#pragma once

#include "Button.h"
#include "UserInterface.h"

#include <SFML\Graphics.hpp>
#include <iostream>

class SelectLevel : public Scene
{
private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	Button level1Button;
	Button level2Button;
	Button level3Button;
	Button backButton;
	bool goToLevel1;
	bool goToLevel2;
	bool goToLevel3;
	bool backToPlay;

public:
	SelectLevel(sf::RenderTexture& window);
	void loadTexture();
	void updateClickButton(sf::RenderWindow& window, bool& held);
	void draw(sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window, bool& held) override;
	GameState getNextScene() override;

};