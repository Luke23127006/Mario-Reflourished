#include "Play.h"

Play::Play(sf::RenderTexture& window)
{
	sf::Color pink(177, 80, 199);
	buttons.push_back(&selectCharacterButton);
	buttons.push_back(&selectLevelButton);
	buttons.push_back(&backButton);
	// Background
	loadTexture();
	playBackground.setPosition(0, 0);
	playBackground.setScale(window.getSize().x / playBackground.getGlobalBounds().width, window.getSize().y / playBackground.getGlobalBounds().height);
	
	// Select character button
	selectCharacterButton.setText("Select Level");
	selectCharacterButton.setButtonSize(sf::Vector2f(300, 50));
	selectCharacterButton.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2, window.getSize().y / 2 - selectCharacterButton.getSize().y));
	selectCharacterButton.setButtonColor(pink);
	selectCharacterButton.setTextColor(sf::Color::White);

	// Select level button
	selectLevelButton.setText("Select Character");
	selectLevelButton.setButtonSize(sf::Vector2f(300, 50));
	selectLevelButton.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2, window.getSize().y / 2 + selectLevelButton.getSize().y));
	selectLevelButton.setButtonColor(pink);
	selectLevelButton.setTextColor(sf::Color::White);

	// Back button
	backButton.setText("Back");
	backButton.setPosition(sf::Vector2f(window.getSize().x - backButton.getSize().x / 2, backButton.getSize().y / 2));
	backButton.setButtonColor(pink);
	backButton.setTextColor(sf::Color::White);
	
	isPressedUp = false;
	isPressedDown = false;
	goToSelectCharacterScene = false;
	goToSelectLevelScene = false;
	backToWelcome = false;
	selectedButton = -1;
	


}
void Play::loadTexture()
{
	//if (!playTexture.loadFromFile("Robot.jpg"))
	//{
	//	std::cerr << "Error loading play texture\n";
	//}
	playTexture = Resources::textures["Play Background"];
	playBackground.setTexture(playTexture);
}


void Play::draw(sf::RenderWindow& window)
{
	window.draw(playBackground);
	selectCharacterButton.draw(window);
	selectLevelButton.draw(window);
	backButton.draw(window);
}



void Play::updateHoverButton(sf::RenderWindow& window)
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
void Play::updateClickButton(sf::RenderWindow& window, float timeElapsed)
{
	if (timeElapsed < debounceTime)
		return;
	if (selectedButton == -1)
	{
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
		|| (sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttons[selectedButton]->isHoverMouse(window)))
	{
		switch (selectedButton)
		{
		case 0:
			goToSelectLevelScene = true;
			break;
		case 1:
			goToSelectCharacterScene = true;
			break;
		case 2:
			backToWelcome = true;
			break;
		default:
			break;
		}
	}
}

void Play::render(sf::RenderWindow& window, float timeElapsed)
{
	
	updateHoverButton(window);
	updateClickButton(window, timeElapsed);
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->colorHoverButton(window);
	}
	draw(window);


}
GameState Play::getNextScene()
{
	if (backToWelcome)
	{
		backToWelcome = false;
		return GameState::Welcome;
	}
	if (goToSelectCharacterScene)
	{
		goToSelectCharacterScene = false;
		return GameState::SelectCharacter;
	}
	if (goToSelectLevelScene)
	{
		goToSelectCharacterScene = false;
		return GameState::SelectLevel;
	}
	return GameState::Play;
	
}
