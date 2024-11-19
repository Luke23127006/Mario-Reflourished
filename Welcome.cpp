#include "Welcome.h"
#include "UserInterface.h"

Welcome::Welcome(sf::RenderTexture& window)
{
	sf::Color pink(177, 80, 199);
	this->buttons.push_back(&this->playButton);
	this->buttons.push_back(&this->exitButton);
	// play
	
	this->playButton.setText("Play");
	this->playButton.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - this->playButton.getSize().y));
	this->playButton.setButtonColor(pink);
	this->playButton.setTextColor(sf::Color::White);

	// exit
	this->exitButton.setText("Exit");
	this->exitButton.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + this->exitButton.getSize().y));
	this->exitButton.setButtonColor(pink);
	this->exitButton.setTextColor(sf::Color::White);
	
	// background
	this->loadTexture();
	/*this->welcomeSprite.setPosition(0, 0);
	this->welcomeSprite.setScale(window.getSize().x / this->welcomeSprite.getGlobalBounds().width, window.getSize().y / this->welcomeSprite.getGlobalBounds().height);*/
	this->welcomeAnimation->setPosition(sf::Vector2f(0, 0));
	this->welcomeAnimation->setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	this->selectedButton = -1;

	this->isPressedUp = false;
	this->isPressedDown = false;
	this->goToPlayScene = false;
}

void Welcome::draw(sf::RenderWindow& window)
{
	//window.draw(this->welcomeSprite);
	this->welcomeAnimation->render(window, sf::Vector2f(0, 0));
	this->playButton.draw(window);
	this->exitButton.draw(window);
}

void Welcome::loadTexture()
{
	/*if (!this->welcomeTexture.loadFromFile("Sinestrea Princess.png"))
	{
		std::cerr << "Error loading welcome texture\n";
		return;
	}*/
	this->welcomeTexture = Resources::textures["Welcome Background"];
	this->welcomeSprite.setTexture(this->welcomeTexture);
	int totalFrames = this->welcomeTexture.getSize().x / 240;
	this->welcomeAnimation = new Animation(this->welcomeTexture, totalFrames, 0.1f, sf::Vector2i(240, 135));
}

void Welcome::updateHoverButton(sf::RenderWindow& window)
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
				this->selectedButton = this->buttons.size();
			}
			this->selectedButton = (this->selectedButton - 1 + this->buttons.size()) % this->buttons.size();
			(*this->buttons[this->selectedButton]).changeHovered();
			this->isPressedUp = true;
			std::cout << "Up\n";
		}
	}
	else {
		this->isPressedUp = false;
	}
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
			this->buttons[this->selectedButton]->changeHovered();
		}
	}
}

void Welcome::updateClickButton(sf::RenderWindow& window)
{
	if (this->selectedButton == -1)
		return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
		|| (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->buttons[this->selectedButton]->isHoverMouse(window)))
	{
		switch (this->selectedButton)
		{
		case 0:
			this->goToPlayScene = true;
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
	this->welcomeAnimation->update(dt, false);
}

void Welcome::render(sf::RenderWindow& window)
{
	this->updateHoverButton(window);
	this->updateClickButton(window);
	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->colorHoverButton(window);
	}
	this->draw(window);
}

void Welcome::update(float dt)
{
	this->updateAnimation(dt);
}

GameState Welcome::getNextScene()
{
	if (this->goToPlayScene)
	{
		this->goToPlayScene = false;
		return GameState::PLAY;
	}
	return GameState::WELCOME;
}

Welcome::~Welcome()
{
	delete this->welcomeAnimation;
}