#include "Welcome.h"


Welcome::Welcome(sf::RenderTexture& window)
{

	
	// play
	this->playButton = new Button();
	this->playButton->setText("Play");
	this->playButton->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - this->playButton->getSize().y));
	this->playButton->addCommand(new changeSceneCommand(GameState::WELCOME, GameState::LOGIN));

	// exit
	this->exitButton = new Button();
	this->exitButton->setText("Exit");
	this->exitButton->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + this->exitButton->getSize().y));
	this->exitButton->addCommand(new changeSceneCommand(GameState::WELCOME, GameState::EXIT));
	// background
	this->loadTexture();
	this->welcomeAnimation->setPosition(sf::Vector2f(0, 0));
	this->welcomeAnimation->setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	
	this->buttons.push_back(this->playButton);
	this->buttons.push_back(this->exitButton);

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


void Welcome::updateClickButton(bool& held)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (held == false)
		{
			held = true;
			if (this->selectedButton >= 0)
			{
				if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->buttons[this->selectedButton]->isHoverMouse())
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
				
					this->buttons[this->selectedButton]->click();
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

void Welcome::render(sf::RenderWindow& window)
{
	
	this->draw(window);
}

void Welcome::update(float dt, bool& held)
{
	this->updateHoverButton();
	this->updateClickButton(held);
	this->updateAnimation(dt);
}

GameState Welcome::getNextScene()
{

	if (selectedButton == -1) return GameState::WELCOME;
	auto nextScene = dynamic_cast<changeSceneCommand*>(this->buttons[this->selectedButton]->getCommand(0));
	if (nextScene != nullptr)
	{
		return nextScene->getScene();
	}
	
}

Welcome::~Welcome()
{
	for (auto& button : this->buttons)
	{
		if (button == nullptr) continue;
		delete button;
	}
	if (this->welcomeAnimation) delete this->welcomeAnimation;
}