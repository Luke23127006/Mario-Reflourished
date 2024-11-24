#include "Play.h"

Play::Play(sf::RenderTexture& window)
{
	sf::Color pink(177, 80, 199);
	this->buttons.push_back(&this->selectCharacterButton);
	this->buttons.push_back(&this->selectLevelButton);
	this->buttons.push_back(&this->backButton);
	// Background
	this->loadTexture();
	this->playBackground.setPosition(0, 0);
	this->playBackground.setScale(window.getSize().x / this->playBackground.getGlobalBounds().width, window.getSize().y / this->playBackground.getGlobalBounds().height);
	
	// Select character button
	this->selectCharacterButton.setText("Select Level");
	this->selectCharacterButton.setButtonSize(sf::Vector2f(300, 50));
	this->selectCharacterButton.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2, window.getSize().y / 2 - this->selectCharacterButton.getSize().y));
	this->selectCharacterButton.setButtonColor(pink);
	this->selectCharacterButton.setTextColor(sf::Color::White);

	// Select level button
	this->selectLevelButton.setText("Select Character");
	this->selectLevelButton.setButtonSize(sf::Vector2f(300, 50));
	this->selectLevelButton.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2, window.getSize().y / 2 + this->selectLevelButton.getSize().y));
	this->selectLevelButton.setButtonColor(pink);
	this->selectLevelButton.setTextColor(sf::Color::White);

	// Back button
	this->backButton.setText("Back");
	this->backButton.setPosition(sf::Vector2f(window.getSize().x - this->backButton.getSize().x / 2, this->backButton.getSize().y / 2));
	this->backButton.setButtonColor(pink);
	this->backButton.setTextColor(sf::Color::White);
	
	// transition scene
	this->goToSelectCharacterScene = false;
	this->goToSelectLevelScene = false;
	this->backToWelcome = false;

}

void Play::loadTexture()
{
	//if (!this->playTexture.loadFromFile("Robot.jpg"))
	//{
	//	std::cerr << "Error loading play texture\n";
	//}
	this->playTexture = Resources::textures["Play Background"];
	this->playBackground.setTexture(this->playTexture);
}

void Play::draw(sf::RenderWindow& window)
{
	window.draw(this->playBackground);
	Scene::draw(window);
}


void Play::updateClickButton(sf::RenderWindow& window, bool& held)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (held == false)
		{
			held = true;
			if (this->selectedButton >= 0)
			{
				if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->buttons[this->selectedButton]->isHoverMouse(window))
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					switch (this->selectedButton)
					{
					case 0:
						this->goToSelectLevelScene = true;
						break;
					case 1:
						this->goToSelectCharacterScene = true;
						break;
					case 2:
						this->backToWelcome = true;
						break;
					default:
						break;
					}
				}
			}
		}
	}
	else held = false;
}

void Play::render(sf::RenderWindow& window, bool& held)
{
	this->updateHoverButton(window);
	this->updateClickButton(window, held);
	this->draw(window);
}

GameState Play::getNextScene()
{
	if (this->backToWelcome)
	{
		this->backToWelcome = false;
		return GameState::WELCOME;
	}
	if (this->goToSelectCharacterScene)
	{
		this->goToSelectCharacterScene = false;
		return GameState::SELECT_CHARACTER;
	}
	if (this->goToSelectLevelScene)
	{
		this->goToSelectCharacterScene = false;
		return GameState::SELECT_LEVEL;
	}
	return GameState::PLAY;
}
