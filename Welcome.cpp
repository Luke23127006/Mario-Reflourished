#include "Welcome.h"
#include "UserInterface.h"

Welcome::Welcome(sf::RenderTexture& window)
{
	sf::Color pink(177, 80, 199);
	this->buttons.push_back(&this->playButton);
	this->buttons.push_back(&this->exitButton);
	// play
<<<<<<< HEAD
	
	playButton.setText("Login");
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

	welcomeAnimation->setPosition(sf::Vector2f(0, 0));
	welcomeAnimation->setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	selectedButton = -1;

	isPressedUp = false;
	isPressedDown = false;
	goToLoginScene = false;
=======

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
>>>>>>> a4c7a06dd011335e9651239fc49e3cea5f2b1eda
}

void Welcome::draw(sf::RenderWindow& window)
{
<<<<<<< HEAD

	welcomeAnimation->render(window, sf::Vector2f(0, 0));
	playButton.draw(window);
	exitButton.draw(window);
=======
	//window.draw(this->welcomeSprite);
	this->welcomeAnimation->render(window, sf::Vector2f(0, 0));
	this->playButton.draw(window);
	this->exitButton.draw(window);
>>>>>>> a4c7a06dd011335e9651239fc49e3cea5f2b1eda
}

void Welcome::loadTexture()
{
<<<<<<< HEAD

	welcomeTexture = Resources::textures["Welcome Background"];
=======
	/*if (!this->welcomeTexture.loadFromFile("Sinestrea Princess.png"))
	{
		std::cerr << "Error loading welcome texture\n";
		return;
	}*/
	this->welcomeTexture = Resources::textures["Welcome Background"];
	this->welcomeSprite.setTexture(this->welcomeTexture);
>>>>>>> a4c7a06dd011335e9651239fc49e3cea5f2b1eda
	int totalFrames = this->welcomeTexture.getSize().x / 240;
	this->welcomeAnimation = new Animation(this->welcomeTexture, totalFrames, 0.1f, sf::Vector2i(240, 135));
}

void Welcome::updateHoverButton(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (!this->isPressedDown)
		{
<<<<<<< HEAD
			if (selectedButton != -1)
					buttons[selectedButton]->changeHovered();
			selectedButton = (selectedButton + 1) % buttons.size();
			buttons[selectedButton]->changeHovered();
			isPressedDown = true;
=======
			if (this->selectedButton != -1)
				(*this->buttons[this->selectedButton]).changeHovered();
			this->selectedButton = (this->selectedButton + 1) % this->buttons.size();
			(*this->buttons[this->selectedButton]).changeHovered();
			this->isPressedDown = true;
>>>>>>> a4c7a06dd011335e9651239fc49e3cea5f2b1eda
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
<<<<<<< HEAD
			if (selectedButton != -1)
				buttons[selectedButton]->changeHovered();
=======
			if (this->selectedButton != -1)
				(*this->buttons[this->selectedButton]).changeHovered();
>>>>>>> a4c7a06dd011335e9651239fc49e3cea5f2b1eda
			else {
				this->selectedButton = this->buttons.size();
			}
<<<<<<< HEAD
			selectedButton = (selectedButton - 1 + buttons.size()) % buttons.size();
			buttons[selectedButton]->changeHovered();
			isPressedUp = true;
=======
			this->selectedButton = (this->selectedButton - 1 + this->buttons.size()) % this->buttons.size();
			(*this->buttons[this->selectedButton]).changeHovered();
			this->isPressedUp = true;
>>>>>>> a4c7a06dd011335e9651239fc49e3cea5f2b1eda
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

void Welcome::updateClickButton(sf::RenderWindow& window, bool& held)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (held == false)
		{
<<<<<<< HEAD
		case 0:
			
			goToLoginScene = true;
			break;
		case 1:
			
			window.close();
			break;
		default:
			break;
=======
			held = true;
			if (this->selectedButton >= 0)
			{
				if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->buttons[this->selectedButton]->isHoverMouse(window))
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
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
>>>>>>> a4c7a06dd011335e9651239fc49e3cea5f2b1eda
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
<<<<<<< HEAD
	if (goToLoginScene)
	{
		goToLoginScene  = false;
		return GameState::LOGIN;
=======
	if (this->goToPlayScene)
	{
		this->goToPlayScene = false;
		return GameState::PLAY;
>>>>>>> a4c7a06dd011335e9651239fc49e3cea5f2b1eda
	}
	return GameState::WELCOME;
}

Welcome::~Welcome()
{
	delete this->welcomeAnimation;
}