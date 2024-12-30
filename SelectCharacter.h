#pragma once
#include "Button.h"
#include "Scene.h"
#include <SFML\Graphics.hpp>
#include<fstream>
#include "Animation.h"
#include "Resources.h"


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
	
	Animation* animation;
	sf::Vector2f animationPosition;

	int selectedSkin;
	int previousSkin;
	// Text box
	Text skinNameText;
public:
	SelectCharacter(sf::RenderTexture& window);
	~SelectCharacter();
	void loadTexture();
	void draw(sf::RenderWindow& window) override;
	void updateCurrentSkin();
	void updateClickButton(bool& held) override;
	void update(float dt, bool& held) override;
	void render(sf::RenderWindow& window) override;
	GameState getNextScene() override;
	void loadSkin();
};



