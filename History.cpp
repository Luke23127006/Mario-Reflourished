#include "History.h"








History::History(sf::RenderTexture& window)
{
	coins.resize(3);
	scores.resize(3);
	coinRects.resize(3);
	scoreRects.resize(3);
	filter = sf::Color(97, 214, 240, 200);
	this->loadData();
	this->createText(window);
	// Background
	this->loadTexture();
	this->historyBackground.setPosition(0, 0);
	this->historyBackground.setScale(window.getSize().x / this->historyBackground.getGlobalBounds().width, window.getSize().y / this->historyBackground.getGlobalBounds().height);
	
	//Wukong
	wukongAnimation->setScale(sf::Vector2f(3.5, 3.5));
	wukongPosition = sf::Vector2f(window.getSize().x - wukongAnimation->getSize().x * 4.f, window.getSize().y / 2 - 100);

	// Back button
	this->backButton = new Button();
	this->backButton->setText("Back");
	this->backButton->setPosition(sf::Vector2f(window.getSize().x - this->backButton->getSize().x / 2, this->backButton->getSize().y / 2.0f));
	this->backButton->addCommand(new changeSceneCommand(GameState::HISTORY, GameState::PLAY));
	this->backButton->setButtonColor(sf::Color(97, 114, 240, 230));
	this->backButton->setTextColor(sf::Color::Black);
	this->buttons.push_back(this->backButton);
	this->selectedButton = 0;


	for (auto& rects : coinRects)
	{
		rects.setFillColor(filter);
		
	}
	for (auto& rects : scoreRects)
	{
		rects.setFillColor(filter);
	}
}



void History::loadTexture()
{
	this->historyTexture = Resources::textures["History Background"];
	this->historyBackground.setTexture(this->historyTexture);
	
	this->wukongTexture = Resources::textures["WUKONG_SMILE"];
	this->wukongAnimation = new Animation(this->wukongTexture, 2, 0.2f, sf::Vector2i(WUKONG_WIDTH, WUKONG_HEIGHT));
	
}






void History::loadData()
{
	std::string line;
	std::vector<std::string> data;
	int coin = 0;
	int score = 0;
	// LEVEL1
	std::ifstream fin("./Resources/UserAccount/" + USER_NAME + "/" "LEVEL 1.txt");
	if (!fin.is_open())
	{
		coins[0] = 0;
		scores[0] = 0;
	}
	else {
		while(std::getline(fin, line))
		{
			data.push_back(line);
		}
		coins[0] = std::stoi(data[0]);
		scores[0] = std::stof(data[1]);
	}
	

	data.clear();
	fin.close();

	// LEVEL2
	fin.open("./Resources/UserAccount/" + USER_NAME + "/" "LEVEL 2.txt");
	if (!fin.is_open())
	{
		coins[1] = 0;
		scores[1] = 0;
	}
	else {
		while (std::getline(fin, line))
		{
			data.push_back(line);
		}
		coins[1] = std::stoi(data[0]);
		scores[1] = std::stof(data[1]);
	}
	

	data.clear();
	fin.close();

	// LEVEL3
	fin.open("./Resources/UserAccount/" + USER_NAME + "/" "LEVEL 3.txt");
	if (!fin.is_open())
	{
		coins[2] = 0;
		scores[2] = 0;
	}
	else {
		while (std::getline(fin, line))
		{
			data.push_back(line);
		}
		coins[2] = std::stoi(data[0]);
		scores[2] = std::stof(data[1]);
	}
	

	data.clear();
	fin.close();
}
void History::createText(sf::RenderTexture& window)
{
	std::stringstream stream;
	Text* text = new Text();
	text->setText("Your History in each map");
	text->setTextSize(70);
	text->setPosition(sf::Vector2f(window.getSize().x / 2 - text->getGlobalBounds().width / 2, 50));
	text->setTextColor(sf::Color(98, 143, 241, 255));
	// 146 77 240
	// Name Map
	Text* textMap1 = new Text();
	textMap1->setText("Map 1 ");
	textMap1->setTextSize(50);
	textMap1->setPosition(sf::Vector2f(50, 200));
	textMap1->setTextColor(sf::Color(146, 277, 240, 255));

	Text* textMap2 = new Text();
	textMap2->setText("Map 2 ");
	textMap2->setTextSize(50);
	textMap2->setPosition(sf::Vector2f(50, 400));
	textMap2->setTextColor(sf::Color(146, 277, 240, 255));

	Text* textMap3 = new Text();
	textMap3->setText("Map 3 ");
	textMap3->setTextSize(50);
	textMap3->setPosition(sf::Vector2f(50, 600));
	textMap3->setTextColor(sf::Color(146, 277, 240, 255));

	// COINS 225 236 40
	Text* textCoin1 = new Text();
	textCoin1->setText("Coins  " + std::to_string(coins[0]));
	textCoin1->setTextSize(50);
	textCoin1->setPosition(sf::Vector2f(300, 200));
	textCoin1->setTextColor(sf::Color(225, 236, 40, 255));
	coinRects[0].setSize(sf::Vector2f(textCoin1->getGlobalBounds().width + 40, textCoin1->getGlobalBounds().height + 40));
	coinRects[0].setPosition(sf::Vector2f(300 - 10, 200 - 10));
	
	Text* textCoin2 = new Text();
	textCoin2->setText("Coins  " + std::to_string(coins[1]));
	textCoin2->setTextSize(50);
	textCoin2->setPosition(sf::Vector2f(300, 400));
	textCoin2->setTextColor(sf::Color(225, 236, 40, 255));
	coinRects[1].setSize(sf::Vector2f(textCoin2->getGlobalBounds().width + 40, textCoin2->getGlobalBounds().height + 40));
	coinRects[1].setPosition(sf::Vector2f(300 - 10, 400 - 10));
	
	Text* textCoin3 = new Text();
	textCoin3->setText("Coins  " + std::to_string(coins[2]));
	textCoin3->setTextSize(50);
	textCoin3->setPosition(sf::Vector2f(300, 600));
	textCoin3->setTextColor(sf::Color(225, 236, 40, 255));
	coinRects[2].setSize(sf::Vector2f(textCoin3->getGlobalBounds().width + 40, textCoin3->getGlobalBounds().height + 40));
	coinRects[2].setPosition(sf::Vector2f(300 - 10, 600 - 10));
	// SCORE

	Text* textScore1 = new Text();
	stream << std::fixed << std::setprecision(2) << scores[0];
	textScore1->setText("Score    " + stream.str());
	textScore1->setTextSize(50);
	textScore1->setPosition(sf::Vector2f(700, 200));
	textScore1->setTextColor(sf::Color::Red);
	scoreRects[0].setSize(sf::Vector2f(textScore1->getGlobalBounds().width + 40, textScore1->getGlobalBounds().height + 40));
	scoreRects[0].setPosition(sf::Vector2f(700 - 10, 200 - 10));
	
	stream.str("");
	stream.clear();
	Text* textScore2 = new Text();
	stream << std::fixed << std::setprecision(2) << scores[1];
	textScore2->setText("Score    " + stream.str());
	textScore2->setTextSize(50);
	textScore2->setPosition(sf::Vector2f(700, 400));
	textScore2->setTextColor(sf::Color::Red);
	scoreRects[1].setSize(sf::Vector2f(textScore2->getGlobalBounds().width + 40, textScore2->getGlobalBounds().height + 40));
	scoreRects[1].setPosition(sf::Vector2f(700 - 10, 400 - 10));

	Text* textScore3 = new Text();
	stream.str("");
	stream.clear();
	stream << std::fixed << std::setprecision(2) << scores[2];
	textScore3->setText("Score    " + stream.str());
	textScore3->setTextSize(50);
	textScore3->setPosition(sf::Vector2f(700, 600));
	textScore3->setTextColor(sf::Color::Red);
	scoreRects[2].setSize(sf::Vector2f(textScore3->getGlobalBounds().width + 40, textScore3->getGlobalBounds().height + 40));
	scoreRects[2].setPosition(sf::Vector2f(700 - 10, 600 - 10));


	


	this->texts.push_back(text);
	this->texts.push_back(textMap1);
	this->texts.push_back(textMap2);
	this->texts.push_back(textMap3);
	this->texts.push_back(textCoin1);
	this->texts.push_back(textCoin2);
	this->texts.push_back(textCoin3);
	this->texts.push_back(textScore1);
	this->texts.push_back(textScore2);
	this->texts.push_back(textScore3);


		
}




void History::draw(sf::RenderWindow& window)
{
	window.draw(this->historyBackground);
	
	wukongAnimation->render(window, wukongPosition);

	for (auto& rect : coinRects)
	{
		window.draw(rect);
	}

	for(auto& rect : scoreRects)
	{
		window.draw(rect);
	}

	for (auto& text : texts)
	{
		text->draw(window);
	}
	Scene::draw(window);
}


void History::update(float dt, bool& held)
{
	wukongAnimation->update(dt, true);
	this->updateHoverButton();
	this->updateClickButton(held);
}


void History::render(sf::RenderWindow& window)
{
	this->draw(window);
}


GameState History::getNextScene()
{
	auto nextScene = dynamic_cast<changeSceneCommand*>(this->buttons[this->selectedButton]->getCommand(0));
	if (nextScene)
	{
		return nextScene->getScene();
	}
	return GameState::HISTORY;
}



History::~History()
{
	delete this->backButton;
	for (auto text : this->texts)
	{
		delete text;
	}
	delete wukongAnimation;
}
