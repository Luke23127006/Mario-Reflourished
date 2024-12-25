#pragma once
#include "Button.h"
#include "Scene.h"
#include <SFML\Graphics.hpp>
#include<fstream>




class SelectCharacter : public Scene
{
private:
	sf::Texture selectSkinTexture;
	sf::Sprite selectSkinBackground;
	
	// Back button
	Button* backButton;
	// Next button
	Button* nextButton;
	float colPosition;
	std::vector<std::string> skinNames;
	sf::Texture skinTexture;
	sf::Sprite skinSprite;
	int selectedSkin;
	// Text box
	Text skinNameText;
public:
	SelectCharacter(sf::RenderTexture& window);
	~SelectCharacter();
	void loadTexture();
	void draw(sf::RenderWindow& window) override;
	void updateCurrentSkin();
	void update(float dt, bool& held) override;
	void render(sf::RenderWindow& window) override;
	GameState getNextScene() override;
	void loadSkin();
};



