#pragma once

#include "Button.h"
#include "Scene.h"

#include <SFML\Graphics.hpp>

class Play : public Scene {
private:
	sf::Texture playTexture;
	sf::Sprite playBackground;
	// Select level button
	Button* selectLevelButton;
	// Select character button
	Button* selectCharacterButton;
	// Back button
	Button* backButton;

	

public:
	Play(sf::RenderTexture& window);
	~Play();
	void loadTexture();
	void draw(sf::RenderWindow& window) override;
	void updateClickButton(bool& held);
	void update(float dt, bool& held) override;
	void render(sf::RenderWindow& window) override;
	GameState getNextScene() override;
};



