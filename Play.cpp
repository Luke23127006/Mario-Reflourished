#include "Play.h"

Play::Play(sf::RenderTexture& window)
{
	
	// Background
	this->loadTexture();
	this->playBackground.setPosition(0, 0);
	this->playBackground.setScale(window.getSize().x / this->playBackground.getGlobalBounds().width, window.getSize().y / this->playBackground.getGlobalBounds().height);
	
	this->NPCAnimation->setScale(sf::Vector2f(3, 3));
	this->NPCposition = sf::Vector2f(window.getSize().x - NPCAnimation->getSize().x * 4, window.getSize().y / 2 + 50);

	// Select level button
	this->selectLevelButton = new Button();
	this->selectLevelButton->setText("Select Level");
	this->selectLevelButton->setButtonSize(sf::Vector2f(350, 50));
	this->selectLevelButton->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - this->selectLevelButton->getSize().y));
	this->selectLevelButton->addCommand(new changeSceneCommand(GameState::PLAY, GameState::SELECT_LEVEL));

	// Select character button
	this->selectCharacterButton = new Button();
	this->selectCharacterButton->setText("Select Character");
	this->selectCharacterButton->setButtonSize(sf::Vector2f(350, 50));
	this->selectCharacterButton->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + this->selectCharacterButton->getSize().y));
	this->selectCharacterButton->addCommand(new changeSceneCommand(GameState::PLAY, GameState::SELECT_CHARACTER));

	// History button
	this->historyButton = new Button();
	this->historyButton->setText("History");
	this->historyButton->setButtonSize(sf::Vector2f(350, 50));
	this->historyButton->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + this->historyButton->getSize().y * 3));
	this->historyButton->addCommand(new changeSceneCommand(GameState::PLAY, GameState::HISTORY));
	// Back button
	this->backButton = new Button();
	this->backButton->setText("Back");
	this->backButton->setPosition(sf::Vector2f(window.getSize().x - this->backButton->getSize().x / 2, this->backButton->getSize().y / 2.0f));
	this->backButton->addCommand(new changeSceneCommand(GameState::PLAY, GameState::WELCOME));

	this->buttons.push_back(this->selectLevelButton);
	this->buttons.push_back(this->selectCharacterButton);
	this->buttons.push_back(this->historyButton);
	this->buttons.push_back(this->backButton);

	for(auto& button : buttons)
	{
		button->setButtonColor(sf::Color(107, 100, 200, 200));
		
	}
	buttons[0]->changeHovered();
}

void Play::loadTexture()
{
	
	this->playTexture = Resources::textures["Play Background"];
	this->NPCtexture = Resources::textures["GOOMBA"];
	this->playBackground.setTexture(this->playTexture);
	this->NPCAnimation = new Animation(this->NPCtexture, 2, 0.2f, sf::Vector2i(GOOMBA_WIDTH, GOOMBA_HEIGHT));
	
}

void Play::draw(sf::RenderWindow& window)
{
	window.draw(this->playBackground);

	NPCAnimation->render(window, NPCposition);

	Scene::draw(window);
}


void Play::update(float dt, bool& held)
{
	NPCAnimation->update(dt, false);
	this->updateHoverButton();
	this->updateClickButton(held);
}
void Play::render(sf::RenderWindow& window)
{
	this->draw(window);	
}

GameState Play::getNextScene()
{
	if (this->selectedButton == -1)
	{
		return GameState::PLAY;
	}
	auto nextScene = dynamic_cast<changeSceneCommand*>(this->buttons[this->selectedButton]->getCommand(0));
	if (nextScene != nullptr)
	{
		return nextScene->getScene();
	}
}

Play::~Play()
{
	for (auto button : this->buttons)
	{
		delete button;
	}
}