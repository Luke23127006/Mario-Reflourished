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


	selectedSkin = selectedButton;
	skinNameText.setText(this->skinNames[selectedSkin]);
	skinNameText.setPosition(sf::Vector2f(window.getSize().x / 2 - skinNameText.getGlobalBounds().width / 2,
		window.getSize().y / 2 - this->buttons[selectedSkin]->getSize().y * 2));
	
	if (!skinTexture.loadFromFile("Resources/Characters/" + this->skinNames[selectedSkin] + "/" + "New " + this->skinNames[selectedSkin] + "/" + this->skinNames[selectedSkin] + ".png"))
	{
			std::cerr << "Error loading skin texture\n";
	}
	else {
				std::cout << "Skin texture loaded\n";
	}
	skinSprite.setTexture(skinTexture);
	skinSprite.setPosition(sf::Vector2f(colPosition + buttons[0]->getSize().x / 2 + 150, window.getSize().y / 2 - this->buttons[0]->getSize().y * 2));
	skinSprite.setScale(10, 10);


}

SelectCharacter::~SelectCharacter()
{
	for (auto button : this->buttons)
	{
		delete button;
	}
}


void SelectCharacter::loadTexture()
{
	this->selectSkinTexture = Resources::textures["Select Skin Background"];
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
	window.draw(this->skinSprite);
	sf::RectangleShape
		rect(sf::Vector2f(100, 100));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color::Blue);
	window.draw(rect);
}

void SelectCharacter::updateCurrentSkin()
{
	if (selectedButton < buttons.size() - 2)
	{
		selectedSkin = selectedButton;
		PLAYER_NAME = this->skinNames[selectedSkin];
	}
	else
		return;
	if (!skinTexture.loadFromFile("Resources/Characters/" + this->skinNames[selectedSkin] + "/" + "new " + this->skinNames[selectedSkin] + "/" + this->skinNames[selectedSkin] + "1.png"))
	{
		std::cerr << "Error loading skin texture\n";
	}
	else {
		std::cout << "Skin texture loaded\n";
	}
	skinSprite.setTexture(skinTexture);
	/*skinSprite.setPosition(sf::Vector2f(colPosition + buttons[0]->getSize().x / 2 + 150, window.getSize().y / 2 - this->buttons[0]->getSize().y * 2));
	skinSprite.setScale(10, 10);*/

}
void SelectCharacter::update(float dt, bool& held)
{
	this->updateHoverButton();
	this->updateCurrentSkin();
	this->updateClickButton(held);
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


