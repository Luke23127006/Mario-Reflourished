#pragma once
#include <SFML\Graphics.hpp>
#include<string>
#include "Button.h"


#include "Animation.h"
#include "Scene.h"

#include <vector>

class Welcome : public Scene {
private:
	sf::Texture welcomeTexture;
	Animation* welcomeAnimation;
	// Play button
	Button* playButton;
	// Exit button
	Button* exitButton;

public:
	Welcome(sf::RenderTexture& window);
	void loadTexture();
	void updateClickButton(bool& held);
	void updateAnimation(float dt);
	void draw(sf::RenderWindow& window) override;
	void update(float dt, bool& held) override;
	void render(sf::RenderWindow& window) override;
	GameState getNextScene() override;
	~Welcome();
};