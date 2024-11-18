#include "Game.h"

void Game::changeScene(GameState nextScene)
{
	bool isChange = false;

	switch (nextScene)
	{
	case GameState::WELCOME:
		if (currentGameState == GameState::WELCOME) return;
		isChange = true;
		currentScene = std::make_unique<Welcome>(renderTexture);
		currentGameState = GameState::WELCOME;
		break;

	case GameState::PLAY:
		if (currentGameState == GameState::PLAY) return;
		std::cout << "Play\n";
		isChange = true;
		currentScene = std::make_unique<Play>(renderTexture);
		currentGameState = GameState::PLAY;
		break;
	case GameState::SELECT_LEVEL:
		if (currentGameState == GameState::SELECT_LEVEL) return;
		std::cout << "SelectLevel\n";
		isChange = true;
		currentScene = std::make_unique<SelectLevel>(renderTexture);
		currentGameState = GameState::SELECT_LEVEL;
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
	this->window->clear();
	window->draw(sprite);
}

void Game::initVariables()
{
	this->window = nullptr;
	renderTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
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
	Resources::Resources();
	this->initVariables();
	this->initWindow();

	this->currentScene = std::make_unique<Welcome>(renderTexture);
	this->currentGameState = GameState::PLAY;
	this->initMap(MAPS_DIRECTORY + "demo_map.png");
	this->initEntities(MAPS_DIRECTORY + "demo_map.png");
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

	this->updateEntities(deltaTime);
	this->updateCollision();
	this->updateCamera(deltaTime);
	this->updateLastPosition();

	this->currentScene->update(deltaTime);
	this->changeScene(currentScene->getNextScene());
}

void Game::updateEntities(float deltaTime)
{
	this->window->clear();
	sf::View viewGame = this->camera.getView(this->window->getSize());
	this->window->setView(viewGame);
	/*if (currentGameState == GameState::Level1)
	{
		Level1* level1 = dynamic_cast<Level1*>(currentScene.get());
		level1->updateCamera(camera);
	}*/
	/*else*/
		//camera.setCenter(sf::Vector2f(renderTexture.getSize().x / 2, renderTexture.getSize().y / 2));
	currentScene->render(*this->window);
}
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
void Game::renderEntities()
{
	for (auto& e : this->entities)
		e->render(*this->window);
}

void Game::updateLastPosition()
{
	for (auto& e : this->entities)
		e->updateLastPosition();
}

void Game::render()
{
	this->window->clear(sf::Color::White);

	// Render items

	this->window->setView(this->camera.getView(this->window->getSize()));
	this->renderEntities();
	this->renderMap();

//void Game::render(float dt)
//{
//
//	window.clear();
//	sf::View viewGame = camera.getView(window.getSize());
//	window.setView(viewGame);
//	/*if (currentGameState == GameState::Level1)
//	{
//		Level1* level1 = dynamic_cast<Level1*>(currentScene.get());
//		level1->updateCamera(camera);
//	}*/
//	/*else*/
//		//camera.setCenter(sf::Vector2f(renderTexture.getSize().x / 2, renderTexture.getSize().y / 2));
//	currentScene->render(window, dt);
//

	this->window->display();
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
