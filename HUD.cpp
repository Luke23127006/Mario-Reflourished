#include "HUD.h"








HUD::HUD(sf::RenderTexture& window, bool isEndlessMode) : Scene()
{
	score = 0;
	time = 0;
	coins = 0;
	this->gameWorld = gameWorld;
	loadTexture();	
	
	this->isEndlessMode = isEndlessMode;

	this->headers.push_back(sf::Text("Score", Resources::fonts["Standard"], 40));
	this->headers.push_back(sf::Text("Time", Resources::fonts["Standard"], 40));
	this->headers.push_back(sf::Text("Coins", Resources::fonts["Standard"], 40));

	this->scoreText = sf::Text(std::to_string(score), Resources::fonts["Standard"], 40);
	this->timeText = sf::Text(std::to_string(time), Resources::fonts["Standard"], 40);
	this->coinText = sf::Text(std::to_string(coins), Resources::fonts["Standard"], 40);
	this->values.push_back(&scoreText);
	this->values.push_back(&timeText);
	this->values.push_back(&coinText);
	
	for (auto& header : this->headers)
	{
		header.setFillColor(sf::Color::Blue);
	}
	for (auto& value : this->values)
	{
		value->setFillColor(sf::Color::Blue);
	}
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

	this->scoreText.setString(std::to_string(score));
	this->timeText.setString(std::to_string(time));
	this->coinText.setString(std::to_string(coins));
}

void HUD::update(float dt, bool& held)
{
	time += dt;

	float sizePerHeader = WINDOW_SIZE.x / this->headers.size();
	for (int i = 0; i < this->headers.size(); i++)
	{
		sf::Vector2f position;
		position.x = sizePerHeader * i + sizePerHeader / 2 - this->headers[i].getGlobalBounds().width / 2;
		position.y = 0.f;
		position += CAMERA_POSITION - sf::Vector2f(WINDOW_SIZE.x, WINDOW_SIZE.y) * 0.5f;
		this->headers[i].setPosition(position);
	}

	for (int i = 0; i < this->values.size(); i++)
	{
		sf::Vector2f position;
		position.x = sizePerHeader * i + sizePerHeader / 2 - this->values[i]->getGlobalBounds().width / 2;
		position.y = this->headers[0].getGlobalBounds().height;
		position += CAMERA_POSITION - sf::Vector2f(WINDOW_SIZE.x, WINDOW_SIZE.y) * 0.5f;
		this->values[i]->setPosition(position);
	}

	calculateData();
}




void HUD::render(sf::RenderWindow& window)
{
	for (auto& header : this->headers)
	{
		window.draw(header);
	}
	for (auto& value : this->values)
	{
		window.draw(*value);
	}
}


GameState HUD::getNextScene()
{
	return GameState::NONE;
}

HUD::~HUD()
{
	//while (!this->powerUp.empty())
	//{
	//	delete this->powerUp.back();
	//	this->powerUp.pop_back();
	//}
}






