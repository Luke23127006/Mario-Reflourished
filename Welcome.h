#pragma once
#include <SFML\Graphics.hpp>
#include<string>
#include "Button.h"
#include<vector>
#include "UserInterface.h"
#include "Animation.h"


class Welcome : public Scene {
private:
	sf::Texture welcomeTexture;
	sf::Sprite welcomeSprite;
	Animation* welcomeAnimation;
	Button playButton;
	Button exitButton;
	std::vector<Button*> buttons;
	int selectedButton;
	bool isPressedUp;
	bool isPressedDown;
	bool goToPlayScene;
public:
	Welcome(sf::RenderTexture& window);
	void loadTexture();
	void updateHoverButton(sf::RenderWindow& window);
	void updateClickButton(sf::RenderWindow& window, bool& held);
	void updateAnimation(float dt);
	void draw(sf::RenderWindow& window);
	void update(float dt) override;
	void render(sf::RenderWindow& window, bool& held) override;
	GameState getNextScene() override;
	~Welcome();
};