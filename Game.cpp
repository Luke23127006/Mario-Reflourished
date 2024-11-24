#include "Game.h"

void Game::changeScene(GameState nextScene)
{
	bool isChange = false;

	switch (nextScene)
	{
	case GameState::WELCOME:
		if (this->currentGameState == GameState::WELCOME) return;
		isChange = true;
		this->currentScene = std::make_unique<Welcome>(this->renderTexture);
		this->currentGameState = GameState::WELCOME;
		break;
	case GameState::LOGIN:
		if (currentGameState == GameState::LOGIN) return;
		isChange = true;
		currentScene = std::make_unique<Login>(renderTexture);
		currentGameState = GameState::LOGIN;
		break;
	case GameState::PLAY:
		if (this->currentGameState == GameState::PLAY) return;
		std::cout << "Play\n";
		isChange = true;
		this->currentScene = std::make_unique<Play>(this->renderTexture);
		this->currentGameState = GameState::PLAY;
		break;
	case GameState::SELECT_LEVEL:
		if (this->currentGameState == GameState::SELECT_LEVEL) return;
		std::cout << "SelectLevel\n";
		isChange = true;
		this->currentScene = std::make_unique<SelectLevel>(this->renderTexture);
		this->currentGameState = GameState::SELECT_LEVEL;
		break;
	case GameState::LEVEL1:
		if (this->currentGameState == GameState::LEVEL1) return;
		std::cout << "Level1\n";
		isChange = true;
		this->currentScene = std::make_unique<AdventureMode>(MAPS_DIRECTORY + "Level 1.png", sf::Vector2f(0.1f * this->window->getSize().x, 0));
		this->currentGameState = GameState::LEVEL1;
		break;
	case GameState::LEVEL2:
		if (this->currentGameState == GameState::LEVEL2) return;
		std::cout << "Level2\n";
		isChange = true;
		this->currentScene = std::make_unique<AdventureMode>(MAPS_DIRECTORY + "Level 2.png", sf::Vector2f(0, 0));
		this->currentGameState = GameState::LEVEL2;
		break;
	default:
		break;
	}
	if (isChange)
	{
		this->applyToMainWindow();
	}
}

void Game::applyToMainWindow()
{
	// Create a sprite to hold the render texture
	sf::Sprite sprite(this->renderTexture.getTexture());

	// Clear the main window and draw the sprite (containing the off-screen rendered content)
	this->window->clear();
	this->window->draw(sprite);
}

void Game::initVariables()
{
	this->window = nullptr;
	this->renderTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->window = new sf::RenderWindow(this->videoMode, "Mario Reflourished");
}

Game::Game()
{
	this->initVariables();
	this->initWindow();

	this->currentScene = std::make_unique<Welcome>(this->renderTexture);
	this->currentGameState = GameState::PLAY;
	this->held = false;
}

Game::~Game()
{
	delete this->window;
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			break;
		}
	}
}

void Game::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::update(float deltaTime)
{
	this->pollEvents();
	this->updateMousePosition();

	this->currentScene->update(deltaTime);
	this->changeScene(this->currentScene->getNextScene());
}

void Game::render()
{
	this->window->clear(sf::Color::White);
	this->window->setView(this->window->getDefaultView());
	this->currentScene->render(*this->window, held);
}

void Game::run()
{
	while (this->window->isOpen())
	{
		float deltaTime = this->clock.restart().asSeconds();

		float FPS = 1 / deltaTime;
		if (FPS < 30.f) continue;

		this->update(deltaTime);
		this->render();
		this->window->display();
	}
}
