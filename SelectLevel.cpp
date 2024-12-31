#include "SelectLevel.h"

SelectLevel::SelectLevel(sf::RenderTexture& window)
{


	// level 1
	this->level1Button = new Button();
	this->level1Button->setText("Original");
	this->level1Button->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - this->level1Button->getSize().y * 3));
	level1Button->addCommand(new changeSceneCommand(GameState::SELECT_LEVEL, GameState::LEVEL1));

	// level 2
	this->level2Button = new Button();
	this->level2Button->setText("  UP!!  ");
	this->level2Button->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - this->level2Button->getSize().y));
	level2Button->addCommand(new changeSceneCommand(GameState::SELECT_LEVEL, GameState::LEVEL2));
	// level 3
	this->level3Button = new Button();
	this->level3Button->setText("How far?");
	this->level3Button->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + this->level3Button->getSize().y));
	level3Button->addCommand(new changeSceneCommand(GameState::SELECT_LEVEL, GameState::LEVEL3));
	// back
	this->backButton = new Button();
	this->backButton->setText("Back");
	this->backButton->setPosition(sf::Vector2f(window.getSize().x - this->backButton->getSize().x / 2, this->backButton->getSize().y / 2));
	this->backButton->addCommand(new changeSceneCommand(GameState::SELECT_LEVEL, GameState::PLAY));
	// background
	this->loadTexture();
	this->backgroundSprite.setPosition(0, 0);
	this->backgroundSprite.setScale(window.getSize().x / this->backgroundSprite.getGlobalBounds().width, window.getSize().y / this->backgroundSprite.getGlobalBounds().height);


	// koopa
	koopaAnimation->setScale(sf::Vector2f(5, 5));
	koopaPosition = sf::Vector2f(koopaAnimation->getSize().x, window.getSize().y / 2 - koopaAnimation->getSize().y / 2);


	this->buttons.push_back(this->level1Button);
	this->buttons.push_back(this->level2Button);
	this->buttons.push_back(this->level3Button);
	this->buttons.push_back(this->backButton);

	for (auto& button : buttons)
	{
		button->setButtonColor(sf::Color(30, 310, 251, 200));
	}
	buttons[0]->changeHovered();

}

void SelectLevel::loadTexture()
{

	this->backgroundTexture = Resources::textures["Select Level Background"];
	this->backgroundSprite.setTexture(this->backgroundTexture);
	this->koopaTexture = Resources::textures["KOOPA"];
	this->koopaAnimation = new Animation(this->koopaTexture, 2, 0.2f, sf::Vector2i(KOOPA_WIDTH, KOOPA_HEIGHT));

}

void SelectLevel::draw(sf::RenderWindow& window)
{
	window.draw(this->backgroundSprite);
	koopaAnimation->render(window, koopaPosition);
	Scene::draw(window);
}




GameState SelectLevel::getNextScene()
{
	
	if (selectedButton == -1) 
		return GameState::SELECT_LEVEL;
	auto nextScene = dynamic_cast<changeSceneCommand*>(this->buttons[this->selectedButton]->getCommand(0));
	if (nextScene != nullptr)
	{
		return nextScene->getScene();
	}
}

void SelectLevel::update(float dt, bool& held)
{
	koopaAnimation->update(dt, false);
	this->updateHoverButton();
	this->updateClickButton(held);
}
void SelectLevel::render(sf::RenderWindow& window)
{

	this->draw(window);
}


SelectLevel:: ~SelectLevel()
{
	for (auto button : buttons)
	{
		delete button;
	}
}