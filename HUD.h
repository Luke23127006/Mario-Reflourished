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
	std::vector<sf::Text> headers;
	std::vector<sf::Text*> values;

	int score;
	int time;
	int coins;
	sf::Text scoreText;
	sf::Text timeText;
	sf::Text coinText;
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