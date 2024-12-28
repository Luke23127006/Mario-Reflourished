#include "VictoryScene.h"








VictoryScene::VictoryScene(sf::RenderTexture& window, std::string mapName)
{
	
	cooldownTime = 6.0f;
	this->mapName = mapName;
	updateHistory();
	this->loadTexture();
	this->createText(window);
	this->victoryBackground.setPosition(0, 0);
	this->victoryBackground.setScale(window.getSize().x / this->victoryBackground.getGlobalBounds().width, window.getSize().y / this->victoryBackground.getGlobalBounds().height);
	bossAnimation = nullptr;
	// Next button
	this->nextButton = new Button();
	this->nextButton->setText("YES");
	if (mapName == "LEVEL 3")
		{
		this->nextButton->setText("REPLAY");
	}
	this->nextButton->setButtonSize(sf::Vector2f(350, 50));
	this->nextButton->setPosition(sf::Vector2f(window.getSize().x / 2  - this->nextButton->getSize().x, window.getSize().y / 2 + 200));
	if (mapName == "LEVEL 1")
	{
		this->nextButton->addCommand(new changeSceneCommand(GameState::VICTORY, GameState::LEVEL2));
		bossAnimation = new Animation(Resources::textures["WUKONG_SMILE"], 2, 0.2f, sf::Vector2i(WUKONG_WIDTH, WUKONG_HEIGHT));
		//bossAnimation = new Animation(Resources::textures["BOWSER"], 3, 0.2f, sf::Vector2i(BOWSER_WIDTH, BOWSER_HEIGHT));
	}
	else if (mapName == "LEVEL 2")
	{
		this->nextButton->addCommand(new changeSceneCommand(GameState::VICTORY, GameState::LEVEL3));
		bossAnimation = new Animation(Resources::textures["WUKONG_SMILE"], 2, 0.2f, sf::Vector2i(WUKONG_WIDTH, WUKONG_HEIGHT));
	}
	else
	{
		this->nextButton->addCommand(new changeSceneCommand(GameState::VICTORY, GameState::LEVEL3));
	}

	// Exit button
	this->exitButton = new Button();
	this->exitButton->setText("NO");
	if(this->mapName == "LEVEL 3")
	{
		this->exitButton->setText("EXIT");
	}
	this->exitButton->setButtonSize(sf::Vector2f(350, 50));
	this->exitButton->setPosition(sf::Vector2f(window.getSize().x / 2 + this->exitButton->getSize().x, window.getSize().y / 2 + 200));
	this->exitButton->addCommand(new changeSceneCommand(GameState::VICTORY, GameState::SELECT_LEVEL));

	if (this->bossAnimation)
	{
		this->bossAnimation->setScale(sf::Vector2f(3, 3));
		bossPosition = sf::Vector2f(bossAnimation->getSize().x, window.getSize().y / 2 - bossAnimation->getSize().y / 2);
	}
	this->buttons.push_back(this->nextButton);
	this->buttons.push_back(this->exitButton);
	this->selectedButton = 0;


}

void VictoryScene::createText(sf::RenderTexture &window)
{
	std::string text1 = "CONGRATULATIONS!";
	std::string text2 = this->mapName != "LEVEL 3" ? "You have completed " + this->mapName   : "Yeah   you have travelled  a  little  far ";
	std::string text3 =  this->mapName != "LEVEL 3" ? "Do you wanna explore more  ? "  : "Your score is   " + std::to_string(int(SCORE));

	Text* t1 = new Text();
	t1->setText(text1);
	t1->setTextSize(110);
	t1->setPosition(sf::Vector2f(window.getSize().x / 2 - t1->getGlobalBounds().width / 2, window.getSize().y / 2 - 300));

	Text* t2 = new Text();
	t2->setText(text2);
	t2->setTextSize(60);
	t2->setPosition(sf::Vector2f(window.getSize().x / 2 - t2->getGlobalBounds().width / 2, window.getSize().y / 2 - 100));



	Text* t3 = new Text();
	t3->setText(text3);
	t3->setTextSize(60);
	t3->setPosition(sf::Vector2f(window.getSize().x / 2 - t3->getGlobalBounds().width / 2, window.getSize().y / 2 + 50));

	this->texts.push_back(t1);
	this->texts.push_back(t2);
	this->texts.push_back(t3);
	
	for (auto& text : texts)
	{
		text->setTextColor(sf::Color(227, 145, 30, 255));
	}

}
void VictoryScene::loadTexture()
{
	this->victoryTexture = Resources::textures["Victory Background"];
	this->victoryBackground.setTexture(this->victoryTexture);
}







void VictoryScene::updateHistory()
{

	std::ifstream fin("./Resources/UserAccount/" + USER_NAME + "/" + mapName + ".txt");
	std::string line;
	std::vector<std::string> history;
	while (std::getline(fin, line))
	{
		history.push_back(line);
	}
	fin.close();
	if (history.size() < 2)
	{
		history.resize(2);
		for (int i = 0; i < history.size(); ++i)
		{
			history[i] = "0";
		}
	}
	float score = std::stof(history[0]);
	int coin = std::stoi(history[1]);

	score = std::max(score, SCORE);
	std::cout << SCORE << std::endl;
	coin = std::max(coin, COINS);


	std::ofstream fout("./Resources/UserAccount/" + USER_NAME + "/" + mapName + ".txt");

	fout << score << std::endl;
	fout << coin << std::endl;
	fout.close();


	

}
void VictoryScene::draw(sf::RenderWindow& window)
{
	window.draw(this->victoryBackground);
	texts[0]->draw(window);
	if (bossAnimation && cooldownTime <= 5.5f)
	{
		bossAnimation->render(window, bossPosition);
	}
	if (cooldownTime <= 4.0f)
	{
		texts[1]->draw(window);
	}
	if (cooldownTime <= 2.0f)
	{
		texts[2]->draw(window);
	}
	if (cooldownTime <= 1.0f)
	{
		this->nextButton->draw(window);
		this->exitButton->draw(window);
	}
}



void VictoryScene::update(float dt, bool& held)
{
	cooldownTime -= dt;
	if (bossAnimation)
	{
		bossAnimation->update(dt, false);
	}
	if (cooldownTime <= 1.0f)
	{
		this->updateHoverButton();
		this->updateClickButton(held);
	}
	
}


void VictoryScene::render(sf::RenderWindow& window)
{
	this->draw(window);

}


GameState VictoryScene::getNextScene()
{
	auto nextScene = dynamic_cast<changeSceneCommand*>(this->buttons[this->selectedButton]->getCommand(0));
	if (nextScene)
	{
		return nextScene->getScene();
	}
	return GameState::VICTORY;
}

VictoryScene::~VictoryScene()
{
	for (auto texts : this->texts)
	{
		delete texts;
	}
	for (auto button : this->buttons)
	{
		delete button;
	}
	if (bossAnimation) delete bossAnimation;
}


