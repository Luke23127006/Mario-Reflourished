#include "SelectLevel.h"

SelectLevel::SelectLevel(sf::RenderTexture& window)
{
	sf::Color pink(177, 80, 199);
	this->buttons.push_back(&this->level1Button);
	this->buttons.push_back(&this->level2Button);
	this->buttons.push_back(&this->level3Button);
	this->buttons.push_back(&this->backButton);
	// level 1
	this->level1Button.setText("Level 1");
	this->level1Button.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - this->level1Button.getSize().y * 3));
	this->level1Button.setButtonColor(pink);
	this->level1Button.setTextColor(sf::Color::White);

	// level 2
	this->level2Button.setText("Level 2");
	this->level2Button.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - this->level2Button.getSize().y));
	this->level2Button.setButtonColor(pink);
	this->level2Button.setTextColor(sf::Color::White);

	// level 3
	this->level3Button.setText("Level 3");
	this->level3Button.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + this->level3Button.getSize().y));
	this->level3Button.setButtonColor(pink);
	this->level3Button.setTextColor(sf::Color::White);

	// back
	this->backButton.setText("Back");
	this->backButton.setPosition(sf::Vector2f(window.getSize().x - this->backButton.getSize().x / 2, this->backButton.getSize().y / 2));
	this->backButton.setButtonColor(pink);
	this->backButton.setTextColor(sf::Color::White);

	// background
	this->loadTexture();
	this->backgroundSprite.setPosition(0, 0);
	this->backgroundSprite.setScale(window.getSize().x / this->backgroundSprite.getGlobalBounds().width, window.getSize().y / this->backgroundSprite.getGlobalBounds().height);

	
	this->goToLevel1 = false;
	this->goToLevel2 = false;
	this->goToLevel3 = false;
	this->backToPlay = false;
}

void SelectLevel::loadTexture()
{
	/*if (!backgroundTexture.loadFromFile("EndTime.jpg"))
	{
		std::cerr << "Error loading background texture\n";
	}*/
	this->backgroundTexture = Resources::textures["Select Level Background"];
	this->backgroundSprite.setTexture(this->backgroundTexture);
}

void SelectLevel::draw(sf::RenderWindow& window)
{
	window.draw(this->backgroundSprite);
	Scene::draw(window);
}



void SelectLevel::updateClickButton(sf::RenderWindow& window, bool& held)
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
						this->goToLevel1 = true;
						break;
					case 1:
						this->goToLevel2 = true;
						break;
					case 2:
						this->goToLevel3 = true;
						break;
					case 3:
						this->backToPlay = true;
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

GameState SelectLevel::getNextScene()
{
	if (this->goToLevel1)
	{
		this->goToLevel1 = false;
		return GameState::LEVEL1;
	}
	if (this->goToLevel2)
	{
		this->goToLevel2 = false;
		return GameState::LEVEL2;
	}
	if (this->goToLevel3)
	{
		this->goToLevel3 = false;
		return GameState::LEVEL3;
	}
	if (this->backToPlay)
	{
		this->backToPlay = false;
		return GameState::PLAY;
	}
	return GameState::SELECT_LEVEL;
}

void SelectLevel::render(sf::RenderWindow& window, bool& held)
{
	this->updateHoverButton(window);
	this->updateClickButton(window, held);
	this->draw(window);
}
