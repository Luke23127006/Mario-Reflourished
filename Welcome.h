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

	// transition scene
	bool goToLoginScene;
public:
	Welcome(sf::RenderTexture& window);
	void loadTexture();
	void updateClickButton(sf::RenderWindow& window, bool& held);
	void updateAnimation(float dt);
	void draw(sf::RenderWindow& window) override;
	void update(float dt) override;
	void render(sf::RenderWindow& window, bool& held) override;
	GameState getNextScene() override;
	~Welcome();
};