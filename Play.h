#pragma once

#include "Button.h"
#include "Scene.h"
#include "Resources.h"
#include <SFML\Graphics.hpp>
#include "Animation.h"
class Play : public Scene {
private:
	sf::Texture playTexture;
	sf::Sprite playBackground;
	// Select level button
	Button* selectLevelButton;
	// Select character button
	Button* selectCharacterButton;
	// History button
	Button* historyButton;
	// Back button
	Button* backButton;

	sf::Texture NPCtexture;
	sf::Vector2f NPCposition;
	Animation* NPCAnimation;

public:
	Play(sf::RenderTexture& window);
	~Play();
	void loadTexture();
	void draw(sf::RenderWindow& window) override;
	void update(float dt, bool& held) override;
	void render(sf::RenderWindow& window) override;
	GameState getNextScene() override;
};



