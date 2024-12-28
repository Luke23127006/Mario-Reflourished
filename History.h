#pragma once
#include "Scene.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Animation.h"



class History : public Scene
{
private:
	sf::Texture historyTexture;
	sf::Sprite historyBackground;
	Button* backButton;
	std::vector<Text*> texts;
	std::vector<int> coins;
	std::vector<float> scores;
	sf::Texture wukongTexture;
	Animation * wukongAnimation;
	sf::Vector2f wukongPosition;
	std::vector<sf::RectangleShape> coinRects;
	std::vector<sf::RectangleShape> scoreRects;
	sf::Color filter;
public:

	History(sf::RenderTexture& window);
	void loadTexture();
	void loadData();
	void createText(sf::RenderTexture& window);
	void draw(sf::RenderWindow& window) override;
	void update(float dt, bool& held) override;
	void render(sf::RenderWindow& window) override;
	GameState getNextScene() override;
	~History();
};


