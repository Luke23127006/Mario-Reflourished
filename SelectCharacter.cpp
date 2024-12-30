#include "SelectCharacter.h"








SelectCharacter::SelectCharacter(sf::RenderTexture& window)
{
	loadTexture();
	loadSkin();
	// Background
	this->selectSkinBackground.setPosition(0, 0);
	this->selectSkinBackground.setScale(window.getSize().x / this->selectSkinBackground.getGlobalBounds().width, window.getSize().y / this->selectSkinBackground.getGlobalBounds().height);

	// Skin button
	for (int i = 0; i < this->skinNames.size(); i++)
	{
		auto button = new Button();
		button->setText(this->skinNames[i]);
		button->setButtonSize(sf::Vector2f(250, 100));
		button->addCommand(new changeSceneCommand(GameState::SELECT_CHARACTER, GameState::SELECT_CHARACTER));
		this->buttons.push_back(button);
	}
	colPosition = window.getSize().x / 2 - this->buttons[0]->getSize().x * 3 / 2;
	float rowPosition = window.getSize().y / 2 - this->buttons[0]->getSize().y * 2;
	for (int i = 0; i < this->skinNames.size(); i++)
	{
		if (rowPosition + this->buttons[i]->getSize().y > window.getSize().y)
		{
			rowPosition = window.getSize().y / 2 - this->buttons[0]->getSize().y * 2;
			colPosition += this->buttons[i]->getSize().x * 1.5;
		}
		this->buttons[i]->setPosition(sf::Vector2f(colPosition , rowPosition));
		rowPosition += this->buttons[i]->getSize().y * 1.5;
	}

	// next Button
	nextButton = new Button();
	nextButton->setText("Next");
	nextButton->setButtonSize(sf::Vector2f(150, 50));
	nextButton->setPosition(sf::Vector2f(window.getSize().x - nextButton->getSize().x / 2, window.getSize().y - nextButton->getSize().y / 2));
	nextButton->addCommand(new changeSceneCommand(GameState::SELECT_CHARACTER, GameState::SELECT_LEVEL));

	// back Button
	backButton = new Button();
	backButton->setText("Back");
	backButton->setButtonSize(sf::Vector2f(150, 50));
	this->backButton->setPosition(sf::Vector2f(window.getSize().x - this->backButton->getSize().x / 2, this->backButton->getSize().y / 2.0f));
	this->backButton->addCommand(new changeSceneCommand(GameState::SELECT_CHARACTER, GameState::PLAY));

	this->buttons.push_back(nextButton);
	this->buttons.push_back(backButton);

	for (auto& button : buttons)
	{
		button->setButtonColor(sf::Color(241, 123, 25, 200));
	}

	selectedSkin = selectedButton;
	skinNameText.setText(this->skinNames[selectedSkin]);
	skinNameText.setPosition(sf::Vector2f(window.getSize().x / 2 - skinNameText.getGlobalBounds().width / 2,
		window.getSize().y / 2 - this->buttons[selectedSkin]->getSize().y * 2));

	

	animationPosition = sf::Vector2f(sf::Vector2f(colPosition + buttons[0]->getSize().x / 2 + 150, window.getSize().y / 2 - this->buttons[0]->getSize().y * 2));
	animation = new Animation(Resources::textures["MARIO_WALK"], 3, 0.2, sf::Vector2i(162 / 3, PLAYER_HEIGHT));
	animation->setSize(sf::Vector2f(300, 300));

}

SelectCharacter::~SelectCharacter()
{
	for (auto button : this->buttons)
	{
		delete button;
	}
	delete animation;
}


void SelectCharacter::loadTexture()
{
	this->selectSkinTexture = Resources::textures["Select Character Background"];
	this->selectSkinBackground.setTexture(this->selectSkinTexture);

}

void SelectCharacter::loadSkin()
{
	std::ifstream file("./Resources/Characters/Characters.txt");
	if (!file.is_open())
	{
		std::cerr << "Error opening file\n";
		file.close();
		return;
	}
	std::string line;
	while (std::getline(file, line))
	{
		this->skinNames.push_back(line);
	}
	file.close();
	for (auto x : this->skinNames)
	{
		std::cout << x << std::endl;
	}

}
void SelectCharacter::draw(sf::RenderWindow& window)
{
	window.draw(this->selectSkinBackground);
	Scene::draw(window);
	animation->render(window, animationPosition);

}

void SelectCharacter::updateCurrentSkin()
{
	if (selectedButton < buttons.size() - 2)
	{

		selectedSkin = selectedButton;
		PLAYER_NAME = skinNames[selectedSkin];
		
	}
	else
		return;
	if (previousSkin == selectedSkin)
		return;
	if (PLAYER_NAME == "Mario")
	{
		delete animation;
		animation = new Animation(Resources::textures["MARIO_WALK"], 3, 0.2, sf::Vector2i(162 / 3, PLAYER_HEIGHT));
	}
	else if (PLAYER_NAME == "Luigi")
	{
		delete animation;
		animation = new Animation(Resources::textures["LUIGI_WALK"], 3, 0.2, sf::Vector2i(162 / 3, PLAYER_HEIGHT));
	}
	animation->setSize(sf::Vector2f(300, 300));
	previousSkin = selectedSkin;
}



void SelectCharacter::updateClickButton(bool& held)
{
	Scene::updateClickButton(held);
	if (selectedButton == selectedSkin)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			held = true;
			if (this->selectedButton >= 0)
			{
				if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->buttons[this->selectedButton]->isHoverMouse())
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					currentControlMode = ControlMode::KEYBOARD;
					this->buttons[this->selectedButton]->changeHovered();
					selectedButton = 2;

				}
			}
			
		}
		else held = false;
		
	}

}
void SelectCharacter::update(float dt, bool& held)
{
	this->updateHoverButton();
	this->updateClickButton(held);
	this->updateCurrentSkin();
	animation->update(dt, false);

}

void SelectCharacter::render(sf::RenderWindow& window)
{
	this->draw(window);

}

GameState SelectCharacter::getNextScene()
{

	auto nextScene = dynamic_cast<changeSceneCommand*>(this->buttons[this->selectedButton]->getCommand(0));
	if (nextScene != nullptr)
	{
		return nextScene->getScene();
	}
}


