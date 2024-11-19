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
	Animation* welcomeAnimation;
	Button playButton;
	Button exitButton;
	std::vector<Button*> buttons;
	int selectedButton;
	bool isPressedUp;
	bool isPressedDown;
	bool goToLoginScene;
public:
	Welcome(sf::RenderTexture& window);
	void loadTexture();
	void updateHoverButton(sf::RenderWindow& window);
	void updateClickButton(sf::RenderWindow& window, float timeElapsed);
	void updateAnimation(float dt);
	void draw(sf::RenderWindow& window);
	void update(float dt) override;
	void render(sf::RenderWindow& window, float timeElapsed) override;
	GameState getNextScene() override;
	~Welcome();
};