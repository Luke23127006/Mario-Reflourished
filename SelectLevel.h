#pragma once

#include "Button.h"
#include "Scene.h"
#include "Animation.h"
#include <SFML\Graphics.hpp>
#include <iostream>

class SelectLevel : public Scene
{
private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	// Level 1 button
	Button* level1Button;
	// Level 2 button
	Button* level2Button;
	// Level 3 button
	Button* level3Button;
	// Back button
	Button* backButton;

	sf::Texture koopaTexture;
	sf::Vector2f koopaPosition;
	Animation* koopaAnimation;

public:
	SelectLevel(sf::RenderTexture& window);
	~SelectLevel();
	void loadTexture();
	void update(float dt, bool& held) override;
	void draw(sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
	GameState getNextScene() override;

};