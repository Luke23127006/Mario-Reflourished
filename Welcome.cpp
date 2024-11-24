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
	
	this->goToLoginScene = false;
}

void Welcome::draw(sf::RenderWindow& window)
{
	//window.draw(this->welcomeSprite);
	this->welcomeAnimation->render(window, sf::Vector2f(0, 0));
	Scene::draw(window);
}

void Welcome::loadTexture()
{
	/*if (!this->welcomeTexture.loadFromFile("Sinestrea Princess.png"))
	{
		std::cerr << "Error loading welcome texture\n";
		return;
	}*/
	this->welcomeTexture = Resources::textures["Welcome Background"];
	int totalFrames = this->welcomeTexture.getSize().x / 240;
	this->welcomeAnimation = new Animation(this->welcomeTexture, totalFrames, 0.1f, sf::Vector2i(240, 135));
}


void Welcome::updateClickButton(sf::RenderWindow& window, bool& held)
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
						this->goToLoginScene = true;
						break;
					case 1:
						window.close();
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

void Welcome::updateAnimation(float dt)
{
	this->welcomeAnimation->update(dt, false);
}

void Welcome::render(sf::RenderWindow& window, bool& held)
{
	this->updateHoverButton(window);
	this->updateClickButton(window, held);
	this->draw(window);
}

void Welcome::update(float dt)
{
	this->updateAnimation(dt);
}

GameState Welcome::getNextScene()
{
	if (this->goToLoginScene)
	{
		this->goToLoginScene = false;
		return GameState::LOGIN;
	}
	return GameState::WELCOME;
}

Welcome::~Welcome()
{
	delete this->welcomeAnimation;
}