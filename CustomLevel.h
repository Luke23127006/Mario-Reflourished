#pragma once

#include "Scene.h"

class CustomLevel : public Scene
{
private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	
	Button* createLevelButton;
	Button* backButton;

public:
	CustomLevel(sf::RenderTexture& window);
	~CustomLevel();
	void loadTexture();
	void draw(sf::RenderWindow& window) override;
	GameState getNextScene() override;

};

