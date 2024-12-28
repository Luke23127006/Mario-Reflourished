#pragma once
#include "Scene.h"
#include "Button.h"
#include "Resources.h"
#include "Text.h"
#include "Animation.h"



class VictoryScene : public Scene
{
private:
	float cooldownTime;
	sf::Texture victoryTexture;
	sf::Sprite victoryBackground;
	Button* nextButton;
	Button* exitButton;
	std::string mapName;
	std::vector<Text*> texts;
	Animation* bossAnimation;
	sf::Vector2f bossPosition;
	
public:
	VictoryScene(sf::RenderTexture& window, std::string mapName);
	void loadTexture();
	void createText(sf::RenderTexture& window);
	void draw(sf::RenderWindow& window) override;
	void update(float dt, bool& held) override;
	void render(sf::RenderWindow& window) override;
	GameState getNextScene() override;
	~VictoryScene();
};

