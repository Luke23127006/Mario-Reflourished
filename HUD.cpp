#include "HUD.h"








HUD::HUD(sf::RenderTexture& window, bool isEndlessMode) : Scene()
{
	score = 0;
	time = 0;
	coins = 0;
	this->gameWorld = gameWorld;
	loadTexture();

	this->isEndlessMode = isEndlessMode;

	int fontSize = 50;
	// headers
	this->headers.push_back(sf::Text("Score", Resources::fonts["Standard"], fontSize));
	this->headers.push_back(sf::Text("Time", Resources::fonts["Standard"], fontSize));
	this->headers.push_back(sf::Text("Coins", Resources::fonts["Standard"], fontSize));

	// headers' values
	this->scoreText = sf::Text(std::to_string(score), Resources::fonts["Standard"], fontSize);
	this->timeText = sf::Text(std::to_string(time), Resources::fonts["Standard"], fontSize);
	this->coinText = sf::Text(std::to_string(coins), Resources::fonts["Standard"], fontSize);
	this->values.push_back(&scoreText);
	this->values.push_back(&timeText);
	this->values.push_back(&coinText);

	// power up borders
	for (int i = 0; i < INT(PowerUpType::NUM_POWER_UPS); i++)
	{
		this->powerUpBorders.push_back(sf::Sprite(Resources::textures["POWER_UP_BORDER"]));
	}

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
	this->timeText.setString(std::to_string(int(time)) + "s");
	this->coinText.setString(std::to_string(coins));

	// power up icons
	this->powerUpIcons.clear();
	this->powerUpBorders.clear();
	this->powerUpTimer.clear();
	auto& powerUps = *POWER_UPS;
	for (int i = 0; i < powerUps.size(); i++)
	{
		this->powerUpIcons.push_back(sf::Sprite(powerUps[i]->getIcon()));

		this->powerUpBorders.push_back(sf::Sprite(Resources::textures["POWER_UP_BORDER"]));

		float percentage = powerUps[i]->getDurationPercentage();
		this->powerUpTimer.push_back(sf::RectangleShape(sf::Vector2f(90.f - 90.f * percentage, 40.f)));
		this->powerUpTimer.back().setFillColor(sf::Color(176, 190, 197));
	}
}

void HUD::update(float dt, bool& held)
{
	time += dt;
	this->calculateData();

	float sizePerHeader = std::max(1.f * ZOOM_LEVEL, ZOOM_LEVEL * ASPECT) / this->headers.size();
	for (int i = 0; i < this->headers.size(); i++)
	{
		sf::Vector2f position;
		position.x = sizePerHeader * i + sizePerHeader / 2 - this->headers[i].getGlobalBounds().width / 2;
		position.y = 0.f;
		position += SCREEN_TOP_LEFT;
		this->headers[i].setPosition(position);
	}
	for (int i = 0; i < this->values.size(); i++)
	{
		sf::Vector2f position;
		position.x = sizePerHeader * i + sizePerHeader / 2 - this->values[i]->getGlobalBounds().width / 2;
		position.y = this->headers[0].getGlobalBounds().height;
		position += SCREEN_TOP_LEFT;
		this->values[i]->setPosition(position);
	}

	float space = 10.f;
	for (int i = 0; i < this->powerUpIcons.size(); i++)
	{
		sf::Vector2f position;
		position.x = SCREEN_TOP_LEFT.x + space;
		position.y = SCREEN_BOTTOM_LEFT.y - (i + 1) * (this->powerUpBorders[i].getGlobalBounds().height + space);
		this->powerUpBorders[i].setPosition(position);
		this->powerUpIcons[i].setPosition(position + sf::Vector2f(2.f, 2.f));
		this->powerUpTimer[i].setPosition(position + sf::Vector2f(56.f + 90.f - this->powerUpTimer[i].getGlobalBounds().width, 7.f));
	}
}



#include "Camera.h"
void HUD::render(sf::RenderWindow& window)
{
	Camera* camera = new Camera();
	window.setView(camera->getView(window.getSize()));
	delete camera;
	for (auto& header : this->headers)
	{
		window.draw(header);
	}
	for (auto& value : this->values)
	{
		window.draw(*value);
	}

	for (int i = 0; i < this->powerUpIcons.size(); i++)
	{
		window.draw(this->powerUpBorders[i]);
		window.draw(this->powerUpIcons[i]);
		window.draw(this->powerUpTimer[i]);
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






