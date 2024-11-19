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

	this->selectedButton = -1;

	this->isPressedUp = false;
	this->isPressedDown = false;
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
	this->level1Button.draw(window);
	this->level2Button.draw(window);
	this->level3Button.draw(window);
	this->backButton.draw(window);
}

void SelectLevel::updateHoverButton(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (!this->isPressedDown)
		{
			if (this->selectedButton != -1)
				(*this->buttons[this->selectedButton]).changeHovered();
			this->selectedButton = (this->selectedButton + 1) % this->buttons.size();
			(*this->buttons[this->selectedButton]).changeHovered();
			this->isPressedDown = true;
			std::cout << "Down\n";
		}
	}
	else {
		this->isPressedDown = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (!this->isPressedUp)
		{
			if (this->selectedButton != -1)
				(*this->buttons[this->selectedButton]).changeHovered();
			else {
				this->selectedButton = static_cast<int>(this->buttons.size());
			}
			this->selectedButton = (this->selectedButton - 1 + this->buttons.size()) % static_cast<int>(this->buttons.size());
			(*this->buttons[this->selectedButton]).changeHovered();
			this->isPressedUp = true;
			std::cout << "Up\n";
		}
	}
	else {
		this->isPressedUp = false;
	}
	// Mouse hover
	for (int i = 0; i < this->buttons.size(); i++)
	{
		if (this->buttons[i]->isHoverMouse(window))
		{
			if (i == this->selectedButton)
			{
				break;
			}
			if (this->selectedButton != -1)
				this->buttons[this->selectedButton]->changeHovered();
			this->selectedButton = i;
			this->buttons[i]->changeHovered();
		}
	}
}

void SelectLevel::updateClickButton(sf::RenderWindow& window)
{
	if (this->selectedButton == -1)
		return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
		|| (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->buttons[this->selectedButton]->isHoverMouse(window)))
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

void SelectLevel::render(sf::RenderWindow& window)
{
	this->updateHoverButton(window);
	this->updateClickButton(window);
	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->colorHoverButton(window);
	}
	this->draw(window);
}
