#include "Pause.h"








Pause::Pause(sf::RenderTexture& window)
{
	// load texture
	Resources::sounds["PAUSE"].play();
	this->loadTexture();
	this->pauseBackground.setPosition(0, 0);
	this->pauseBackground.setScale(window.getSize().x / this->pauseBackground.getGlobalBounds().width, window.getSize().y / this->pauseBackground.getGlobalBounds().height);

	// resume button
	this->resumeButton = new Button();
	this->resumeButton->setText("Continue");
	this->resumeButton->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 2 * this->resumeButton->getSize().y));
	this->resumeButton->addCommand(new changeSceneCommand(GameState::PAUSE, GameState::RESUME));

	this->resumeButton->setButtonColor(sf::Color (0, 0, 0, 150));

	// replay button
	this->replayButton = new Button();
	this->replayButton->setText("Replay");
	this->replayButton->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	this->replayButton->addCommand(new changeSceneCommand(GameState::PAUSE, GameState::REPLAY));

	this->replayButton->setButtonColor(sf::Color(0, 0, 0, 150));

	// exit button
	this->exitButton = new Button();
	this->exitButton->setText("Exit");
	this->exitButton->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + 2 * this->exitButton->getSize().y));
	this->exitButton->addCommand(new changeSceneCommand(GameState::PAUSE, GameState::PLAY));

	this->exitButton->setButtonColor(sf::Color(0, 0, 0, 150));


	// add buttons
	this->buttons.push_back(this->resumeButton);
	this->buttons.push_back(this->replayButton);
	this->buttons.push_back(this->exitButton);
	buttons[0]->changeHovered();
	//this->pauseBackground.setScale(window.getSize().x / this->pauseBackground.getGlobalBounds().width, window.getSize().y / this->pauseBackground.getGlobalBounds().height);
}

void Pause::loadTexture()
{
	this->pauseTexture = Resources::textures["Pause Background"];
	this->pauseBackground.setTexture(this->pauseTexture);
	
	//Blur
	sf::RenderTexture tempRenderTexture;
	tempRenderTexture.create(this->pauseTexture.getSize().x, this->pauseTexture.getSize().y);
	tempRenderTexture.clear(sf::Color::Transparent);
	sf::Sprite blurrSprite(this->pauseTexture);

	// Merge Blur Texture
	sf::Sprite blurredSprite(this->pauseTexture);
	for (int i = -5; i <= 5; ++i) {
		for (int j = -5; j <= 5; ++j) {
			if (i != 0 || j != 0) {
				blurredSprite.setPosition(i, j);
				blurredSprite.setColor(sf::Color(255, 255, 255, 39)); // Giảm alpha
				tempRenderTexture.draw(blurredSprite);
			}
		}
	}
	// For darkening
	sf::RectangleShape tempBlurRect(sf::Vector2f(this->pauseTexture.getSize().x, this->pauseTexture.getSize().y));
	tempBlurRect.setFillColor(sf::Color(0, 0, 0, 50));
	tempRenderTexture.draw(tempBlurRect);
	
	
	tempRenderTexture.display();


	// Update
	this->pauseTexture = tempRenderTexture.getTexture();
	this->pauseBackground.setTexture(this->pauseTexture);
}


void Pause::draw(sf::RenderWindow& window)
{
	window.draw(this->pauseBackground);
	Scene::draw(window);
}

void Pause::update(float dt, bool& held)
{
	this->updateHoverButton();
	this->updateClickButton(held);
}


void Pause::render(sf::RenderWindow& window)
{
	this->draw(window);
}

GameState Pause::getNextScene()
{
	if (this->selectedButton == -1)
	{
		return GameState::PAUSE;
	}
	auto nextScene = dynamic_cast<changeSceneCommand*>(this->buttons[this->selectedButton]->getCommand(0));
	if (nextScene != nullptr)
	{
		return nextScene->getScene();
	}
}






Pause::~Pause()
{
	for (auto button : this->buttons)
	{
		delete button;
	}
	Resources::textures.erase("Pause Background");
}