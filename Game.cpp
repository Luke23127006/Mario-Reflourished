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
		debounceClock.restart();
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
		//this->currentScene = std::make_unique<Level1>(this->renderTexture);
		this->currentGameState = GameState::LEVEL1;
		this->initMap(MAPS_DIRECTORY + "demo_map.png");
		this->initEntities(MAPS_DIRECTORY + "demo_map.png");
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

void Game::initMap(std::string fileName)
{
	this->map = new Map(fileName, sf::Vector2f(0, 0));
}

void Game::initEntities(std::string fileName)
{
	sf::Image image;
	image.loadFromFile(fileName);

	this->entities.clear();
	for (int i = 0; i < image.getSize().x; i++)
		for (int j = 0; j < image.getSize().y; j++)
		{
			sf::Color color = image.getPixel(i, j);
			if (color == sf::Color(237, 28, 36, 255))
			{
				this->player = new Player(sf::Vector2f(42, 48), sf::Vector2f(i * 50, j * 50));
				this->entities.insert(this->entities.begin(), this->player);
			}
		}
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

	while (!this->entities.empty())
	{
		delete this->entities.back();
		this->entities.pop_back();
	}

	delete this->map;
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

	//this->updateEntities(deltaTime);
	//this->updateCollision();
	//this->updateCamera(deltaTime);
	//this->updateLastPosition();

	switch (this->currentGameState)
	{
	case GameState::LEVEL1:
		this->updateEntities(deltaTime);
		this->updateCollision();
		this->updateCamera(deltaTime);
		this->updateLastPosition();
		break;
	default:
		this->currentScene->update(deltaTime);
		this->changeScene(this->currentScene->getNextScene());
		break;
	}
}

void Game::updateEntities(float deltaTime)
{
	for (auto& e : this->entities)
		e->update(deltaTime);
}

void Game::updateCollision()
{
	for (auto& e : this->entities)
	{
		Collision::handle_entity_map(e, this->map);
	}
}

void Game::updateCamera(float deltaTime)
{
	if (!this->player) return;
	this->camera.setPosition(this->player->getPosition());
}

void Game::updateLastPosition()
{
	for (auto& e : this->entities)
		e->updateLastPosition();
}

void Game::render()
{
	this->window->clear(sf::Color::White);
	sf::View viewGame = this->camera.getView(this->window->getSize());
	this->window->setView(viewGame);

	switch (this->currentGameState)
	{
	case GameState::LEVEL1:
		this->renderMap();
		this->renderEntities();
		break;
	default:
		this->currentScene->render(*this->window, held);
		break;
	}
}

void Game::renderEntities()
{
	for (auto& e : this->entities)
		e->render(*this->window);
}

void Game::renderMap()
{
	this->map->render(*this->window);
}

void Game::run()
{
	while (this->window->isOpen())
	{
		float deltaTime = this->clock.restart().asSeconds();
		this->update(deltaTime);
		this->render();
		this->window->display();
	}
}