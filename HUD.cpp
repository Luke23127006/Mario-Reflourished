#include "HUD.h"








HUD::HUD(sf::RenderTexture& window, bool isEndlessMode) : Scene()
{
	score = 0;
	time = 0;
	coins = 0;
	this->gameWorld = gameWorld;
	loadTexture();	
	
	this->isEndlessMode = isEndlessMode;
	scoreText.setText("Score: " + std::to_string(score));
	scoreText.setTextColor(sf::Color::Blue);
	scoreText.setTextSize(40);
	timeText.setText("Time: " + std::to_string(time) + "  s");
	timeText.setTextColor(sf::Color::Blue);
	timeText.setTextSize(30);
	coinText.setText("Coins: " + std::to_string(coins) + "  coins");
	coinText.setTextColor(sf::Color::Blue);
	coinText.setTextSize(30);

}

void HUD::loadTexture()
{

}


void HUD::calculateData()
{

	score = SCORE;
	int beatEnemies = BEAT_ENEMY;
	int beatBoss = BEAT_BOSS;
	int coins = COINS;


	score += coins * 10 + beatEnemies * 100 + beatBoss * 1000;
	if (this->isEndlessMode)
	{
		SCORE += 0.001;
	}
	scoreText.setText("Score      " + std::to_string(int(score)));
	timeText.setText("Time      " + std::to_string(int(time)) + "  s");
	coinText.setText("Coins      " + std::to_string(coins) + "  coins");
	sf::Vector2f window = SCREEN_TOP_RIGHT - SCREEN_BOTTOM_LEFT;
	sf::Vector2f scorePosition = sf::Vector2f(SCREEN_TOP_LEFT.x + window.x / 20, SCREEN_TOP_LEFT.y);
	sf::Vector2f timePosition = sf::Vector2f(SCREEN_TOP_LEFT.x + window.x * 2.f / 5, SCREEN_TOP_LEFT.y);
	sf::Vector2f coinPosition = sf::Vector2f(SCREEN_TOP_LEFT.x + window.x * 4 / 5, SCREEN_TOP_LEFT.y);
	scoreText.setPosition(scorePosition);
	timeText.setPosition(timePosition);
	coinText.setPosition(coinPosition);


}

void HUD::update(float dt, bool& held)
{
	time += dt;
	calculateData();
}




void HUD::render(sf::RenderWindow& window)
{
	scoreText.draw(window);
	timeText.draw(window);
	coinText.draw(window);
}


GameState HUD::getNextScene()
{
	return GameState::NONE;
}

HUD::~HUD()
{
}






