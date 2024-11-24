#pragma once

#include "Button.h"
#include "UserInterface.h"

#include <SFML\Graphics.hpp>

class Play : public Scene {
private:
	sf::Texture playTexture;
	sf::Sprite playBackground;
	Button selectCharacterButton;
	Button selectLevelButton;
	Button backButton;
	
	// transition scene
	bool goToSelectCharacterScene;
	bool goToSelectLevelScene;
	bool backToWelcome;
public:
	Play(sf::RenderTexture& window);
	void loadTexture();
	void draw(sf::RenderWindow& window) override;
	void updateClickButton(sf::RenderWindow& window, bool& held);
	void render(sf::RenderWindow& window, bool& held) override;
	GameState getNextScene() override;
};



