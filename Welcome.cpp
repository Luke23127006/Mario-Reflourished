#include "Welcome.h"
#include "UserInterface.h"






Welcome::Welcome(sf::RenderTexture& window)
{
	sf::Color pink(177, 80, 199);
	buttons.push_back(&playButton);
	buttons.push_back(&exitButton);
	// play
	
	playButton.setText("Play");
	playButton.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - playButton.getSize().y));
	playButton.setButtonColor(pink);
	playButton.setTextColor(sf::Color::White);

	// exit
	exitButton.setText("Exit");
	exitButton.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + exitButton.getSize().y));
	exitButton.setButtonColor(pink);
	exitButton.setTextColor(sf::Color::White);
	
	// background
	loadTexture();
	/*welcomeSprite.setPosition(0, 0);
	welcomeSprite.setScale(window.getSize().x / welcomeSprite.getGlobalBounds().width, window.getSize().y / welcomeSprite.getGlobalBounds().height);*/
	welcomeAnimation->setPosition(sf::Vector2f(0, 0));
	welcomeAnimation->setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	selectedButton = -1;

	isPressedUp = false;
	isPressedDown = false;
	goToPlayScene = false;
}

void Welcome::draw(sf::RenderWindow& window)
{
	//window.draw(welcomeSprite);
	welcomeAnimation->render(window, sf::Vector2f(0, 0));
	playButton.draw(window);
	exitButton.draw(window);
}

void Welcome::loadTexture()
{
	/*if (!welcomeTexture.loadFromFile("Sinestrea Princess.png"))
	{
		std::cerr << "Error loading welcome texture\n";
		return;
	}*/
	welcomeTexture = Resources::textures["Welcome Background"];
	welcomeSprite.setTexture(welcomeTexture);
	int totalFrames = this->welcomeTexture.getSize().x / 240;
	welcomeAnimation = new Animation(welcomeTexture, totalFrames, 0.1f, sf::Vector2i(240, 135));
}


void Welcome::updateHoverButton(sf::RenderWindow& window)
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
				selectedButton = buttons.size();
			}
			selectedButton = (selectedButton - 1 + buttons.size()) % buttons.size();
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
			buttons[selectedButton]->changeHovered();
		}
	}
}

void Welcome::updateClickButton(sf::RenderWindow& window)
{
	if (selectedButton == -1)
		return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
		|| (sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttons[selectedButton]->isHoverMouse(window)))
	{
		switch (selectedButton)
		{
		case 0:
			
			goToPlayScene = true;
			break;
		case 1:
			
			window.close();
			break;
		default:
			break;
		}
	}
}
void Welcome::updateAnimation(float dt)
{
	welcomeAnimation->update(dt,false);
}
void Welcome::render(sf::RenderWindow& window)
{
	
	
	updateHoverButton(window);
	updateClickButton(window);
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->colorHoverButton(window);
	}
	draw(window);

}

void Welcome::update(float dt)
{
	updateAnimation(dt);
}
GameState Welcome::getNextScene()
{
	if (goToPlayScene)
	{
		goToPlayScene  = false;
		return GameState::PLAY;
	}
	return GameState::WELCOME;
}

Welcome::~Welcome()
{
	delete welcomeAnimation;
}