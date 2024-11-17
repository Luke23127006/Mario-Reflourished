#include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->window = new sf::RenderWindow(this->videoMode, "Mario Reflourished");
}

void Game::initMap(std::string fileName)
{
	this->map = new Map(fileName, sf::Vector2i(50, 30), sf::Vector2f(0, 0));
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
				this->player = new Player(sf::Vector2f(50, 50), sf::Vector2f(i * 50, j * 50));
				this->entities.insert(this->entities.begin(), this->player);
			}
		}
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
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

	this->updateCamera(deltaTime);
	this->updateEntities(deltaTime);
}

void Game::updateEntities(float deltaTime)
{
	for (auto& e : this->entities)
		e->update(deltaTime);
}

void Game::updateCamera(float deltaTime)
{
	if (!this->player) return;
	this->camera.setPosition(this->player->getPosition());
}

void Game::render()
{
	this->window->clear(sf::Color::White);

	// Render items

	/*switch (this->gameState)
	{
	case GameState::HOME:
		break;

	case GameState::SELECT_CHARACTER:
		break;

	case GameState::SELECT_LEVEL:
		break;

	case GameState::SETTING:
		break;

	case GameState::PLAYING:
		break;

	case GameState::PAUSED:
		break;

	case GameState::GAME_OVER:
		break;

	}*/

	this->window->setView(this->camera.getView(this->window->getSize()));
	this->renderEntities();
	this->renderMap();
	// End render

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
