//#include "Game.h"
//
//void Game::initVariables()
//{
//	this->window = nullptr;
//}
//
//void Game::initWindow()
//{
//	this->videoMode = sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
//	this->window = new sf::RenderWindow(this->videoMode, "Mario Reflourished");
//}
//
//Game::Game()
//{
//	this->initVariables();
//	this->initWindow();
//}
//
//Game::~Game()
//{
//	delete this->window;
//
//	while (!this->entities.empty())
//	{
//		delete this->entities.back();
//		this->entities.pop_back();
//	}
//}
//
//void Game::pollEvents()
//{
//	while (this->window->pollEvent(this->ev))
//	{
//		switch (this->ev.type)
//		{
//		case sf::Event::Closed:
//			this->window->close();
//			break;
//		case sf::Event::KeyPressed:
//			break;
//		}
//	}
//}
//
//void Game::updateMousePosition()
//{
//	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
//	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
//}
//
//const bool Game::running() const
//{
//	return this->window->isOpen();
//}
//
//void Game::update(float deltaTime)
//{
//	this->pollEvents();
//	this->updateMousePosition();
//}
//
//void Game::render()
//{
//	this->window->clear(sf::Color::Cyan);
//
//	// Render items
//
//	switch (this->gameState)
//	{
//	case GameState::HOME:
//		break;
//
//	case GameState::SELECT_CHARACTER:
//		break;
//
//	case GameState::SELECT_LEVEL:
//		break;
//
//	case GameState::SETTING:
//		break;
//
//	case GameState::PLAYING:
//		this->renderEntities();
//		break;
//
//	case GameState::PAUSED:
//		break;
//
//	case GameState::GAME_OVER:
//		break;
//
//	}
//
//	// End render
//
//	this->window->display();
//}
//
//void Game::renderEntities()
//{
//	for (auto& e : this->entities)
//		e->render(*this->window);
//}






#include "Game.h"








Game::Game()
{
	window.create(sf::VideoMode(1280, 720), "Mario iu e", sf::Style::Default);
	renderTexture.create(1280, 720);
	currentScene = std::make_unique<Welcome>(renderTexture);
	currentGameState = GameState::Welcome;

}

void Game::changeScene(GameState nextScene)
{
	bool isChange = false;

	switch (nextScene)
	{
	case GameState::Welcome:
		if (currentGameState == GameState::Welcome) return;
		isChange = true;
		currentScene = std::make_unique<Welcome>(renderTexture);
		debounceClock.restart();
		currentGameState = GameState::Welcome;
		break;

	case GameState::Play:
		if (currentGameState == GameState::Play) return;
		std::cout << "Play\n";
		isChange = true;
		currentScene = std::make_unique<Play>(renderTexture);
		debounceClock.restart();
		currentGameState = GameState::Play;
		break;
	case GameState::SelectLevel:
		if (currentGameState == GameState::SelectLevel) return;
		std::cout << "SelectLevel\n";
		isChange = true;
		currentScene = std::make_unique<SelectLevel>(renderTexture);
		debounceClock.restart();
		currentGameState = GameState::SelectLevel;
		break;
	//case GameState::Level1:
	//	if (currentGameState == GameState::Level1) return;
	//	std::cout << "Level1\n";
	//	isChange = true;
	//	currentScene = std::make_unique<Level1>(renderTexture);
	//	debounceClock.restart();
	//	currentGameState = GameState::Level1;
	//	break;
	default:
		break;
	}
	if (isChange)
	{
		applyToMainWindow();
	}
}
void Game::applyToMainWindow()
{
	// Create a sprite to hold the render texture
	sf::Sprite sprite(renderTexture.getTexture());

	// Clear the main window and draw the sprite (containing the off-screen rendered content)
	window.clear();
	window.draw(sprite);
	window.display();
}

void Game::render(float dt)
{

	window.clear();
	sf::View viewGame = camera.getView(window.getSize());
	window.setView(viewGame);
	/*if (currentGameState == GameState::Level1)
	{
		Level1* level1 = dynamic_cast<Level1*>(currentScene.get());
		level1->updateCamera(camera);
	}*/
	/*else*/
		//camera.setCenter(sf::Vector2f(renderTexture.getSize().x / 2, renderTexture.getSize().y / 2));
	currentScene->render(window, dt);


}
void Game::run()
{

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();

		}
		float dt = clock.restart().asSeconds();
		currentScene->update(dt);
		changeScene(currentScene->getNextScene());
		render(debounceClock.getElapsedTime().asSeconds());
		window.display();


	}
}