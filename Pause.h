#pragma once
#include "Scene.h"
#include "Button.h"
#include "SFML\Graphics.hpp"





class Pause : public Scene
{
private:
	sf::Texture pauseTexture;
	sf::Sprite pauseBackground;
	Button* resumeButton;
	Button* replayButton;
	Button* exitButton;
public:
	Pause(sf::RenderTexture& window);
	void loadTexture();
	void draw(sf::RenderWindow& window) override;
	void update(float dt, bool& held) override;
	void render(sf::RenderWindow& window) override;
	GameState getNextScene() override;
	~Pause();
};
