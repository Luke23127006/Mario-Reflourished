#pragma once
#include "Scene.h"
#include "Button.h"
#include "SFML\Graphics.hpp"
#include<unordered_map>
#include<string>
#include "AdventureMode.h"
#include "Resources.h"

class HUD : public Scene
{
private:
	
	float score;
	float time;
	int coins;
	Text scoreText;
	Text timeText;
	Text coinText;
	bool isEndlessMode;
	std::vector<Button*> powerUp;
	std::unordered_map<std::string, double> initialData;
	std::unordered_map<std::string, double> worldData;
	Scene* gameWorld;
public:
	HUD(sf::RenderTexture& window, bool isEndlessMode);
	void loadTexture();
	//void draw(sf::RenderWindow& window) override;
	void update(float dt, bool& held) override;
	void render(sf::RenderWindow& window) override;
	void calculateData();
	GameState getNextScene() override;
	~HUD();
};