#include "SelectLevel.h"








SelectLevel::SelectLevel(sf::RenderTexture& window)
{
	sf::Color pink(177, 80, 199);
	buttons.push_back(&level1Button);
	buttons.push_back(&level2Button);
	buttons.push_back(&level3Button);
	buttons.push_back(&backButton);
	// level 1
	level1Button.setText("Level 1");
	level1Button.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - level1Button.getSize().y * 3));
	level1Button.setButtonColor(pink);
	level1Button.setTextColor(sf::Color::White);

	// level 2
	level2Button.setText("Level 2");
	level2Button.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - level2Button.getSize().y));
	level2Button.setButtonColor(pink);
	level2Button.setTextColor(sf::Color::White);

	// level 3
	level3Button.setText("Level 3");
	level3Button.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + level3Button.getSize().y));
	level3Button.setButtonColor(pink);
	level3Button.setTextColor(sf::Color::White);

	// back
	backButton.setText("Back");
	backButton.setPosition(sf::Vector2f(window.getSize().x - backButton.getSize().x / 2, backButton.getSize().y / 2));
	backButton.setButtonColor(pink);
	backButton.setTextColor(sf::Color::White);

	// background
	loadTexture();
	backgroundSprite.setPosition(0, 0);
	backgroundSprite.setScale(window.getSize().x / backgroundSprite.getGlobalBounds().width, window.getSize().y / backgroundSprite.getGlobalBounds().height);

	selectedButton = -1;

	isPressedUp = false;
	isPressedDown = false;
	goToLevel1 = false;
	goToLevel2 = false;
	goToLevel3 = false;
	backToPlay = false;
}

void SelectLevel::loadTexture()
{
	/*if (!backgroundTexture.loadFromFile("EndTime.jpg"))
	{
		std::cerr << "Error loading background texture\n";
	}*/
	backgroundTexture = Resources::textures["Select Level Background"];
	backgroundSprite.setTexture(backgroundTexture);
}

void SelectLevel::draw(sf::RenderWindow& window)
{
	window.draw(backgroundSprite);
	level1Button.draw(window);
	level2Button.draw(window);
	level3Button.draw(window);
	backButton.draw(window);
}

void SelectLevel::updateHoverButton(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{

		if (!isPressedDown)
		{
			if (selectedButton != -1)
				(*buttons[selectedButton]).changeHovered();
			selectedButton = (selectedButton + 1) % buttons.size();
			(*buttons[selectedButton]).changeHovered();
			isPressedDown = true;
			std::cout << "Down\n";
		}

	}
	else {
		isPressedDown = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{

		if (!isPressedUp)
		{
			if (selectedButton != -1)
				(*buttons[selectedButton]).changeHovered();
			else {
				selectedButton = static_cast<int>(buttons.size());
			}
			selectedButton = (selectedButton - 1 + buttons.size()) % static_cast<int>(buttons.size());
			(*buttons[selectedButton]).changeHovered();
			isPressedUp = true;
			std::cout << "Up\n";
		}

	}
	else {
		isPressedUp = false;
	}
	// Mouse hover
	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i]->isHoverMouse(window))
		{
			if (i == selectedButton)
			{
				break;
			}
			if (selectedButton != -1)
				buttons[selectedButton]->changeHovered();
			selectedButton = i;
			buttons[i]->changeHovered();
		}
	}
}







void SelectLevel::updateClickButton(sf::RenderWindow& window, float timeElapsed)
{
	if (timeElapsed < debounceTime)
		return;
	if (selectedButton == -1)
		return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
		|| (sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttons[selectedButton]->isHoverMouse(window)))
	{
		switch (selectedButton)
		{
		case 0:
			goToLevel1 = true;
			break;
		case 1:
			goToLevel2 = true;
			break;
		case 2:
			goToLevel3 = true;
			break;
		case 3:
			backToPlay = true;
			break;
		default:
			break;

		}
	}
}

GameState SelectLevel::getNextScene()
{
	if (goToLevel1)
	{
		goToLevel1 = false;
		return GameState::LEVEL1;
	}
	if (goToLevel2)
	{
		goToLevel2 = false;
		return GameState::LEVEL2;
	}
	if (goToLevel3)
	{
		goToLevel3 = false;
		return GameState::LEVEL3;
	}
	if (backToPlay)
	{
		backToPlay = false;
		return GameState::PLAY;
	}
	return GameState::SELECT_LEVEL;
}

void SelectLevel::render(sf::RenderWindow& window, float timeElapsed)
{
	updateHoverButton(window);
	updateClickButton(window, timeElapsed);
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->colorHoverButton(window);
	}
	draw(window);
}

