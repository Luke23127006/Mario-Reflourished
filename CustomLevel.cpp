#include "CustomLevel.h"

CustomLevel::CustomLevel(sf::RenderTexture& window)
{

	// create level
	this->createLevelButton = new Button();
	this->createLevelButton->setText("Create level");
	this->createLevelButton->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + this->createLevelButton->getSize().y * 4));
	createLevelButton->addCommand(new changeSceneCommand(GameState::CUSTOM_LEVEL, GameState::CUSTOM_MODE));

	// back
	this->backButton = new Button();
	this->backButton->setText("Back");
	this->backButton->setPosition(sf::Vector2f(window.getSize().x - this->backButton->getSize().x / 2, this->backButton->getSize().y / 2));
	this->backButton->addCommand(new changeSceneCommand(GameState::CUSTOM_LEVEL, GameState::SELECT_LEVEL));

	this->buttons.push_back(this->createLevelButton);
	this->buttons.push_back(this->backButton);

	buttons[0]->changeHovered();
}

CustomLevel::~CustomLevel()
{
	for (auto button : buttons)
	{
		delete button;
	}
}

void CustomLevel::loadTexture()
{
}

void CustomLevel::draw(sf::RenderWindow& window)
{
	Scene::draw(window);
}

GameState CustomLevel::getNextScene()
{
	if (selectedButton == -1)
		return GameState::CUSTOM_LEVEL;
	auto nextScene = dynamic_cast<changeSceneCommand*>(this->buttons[this->selectedButton]->getCommand(0));
	if (nextScene != nullptr)
	{
		return nextScene->getScene();
	}
}
