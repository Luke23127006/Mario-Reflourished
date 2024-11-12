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

Game::Game()
{
	this->initVariables();
	this->initWindow();
}

Game::~Game()
{
	delete this->window;

	while (!this->entities.empty())
	{
		delete this->entities.back();
		this->entities.pop_back();
	}
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
}

void Game::render()
{
	this->window->clear(sf::Color::Cyan);

	// Render items

	switch (this->gameState)
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
		this->renderEntities();
		break;

	case GameState::PAUSED:
		break;

	case GameState::GAME_OVER:
		break;

	}

	// End render

	this->window->display();
}

void Game::renderEntities()
{
	for (auto& e : this->entities)
		e->render(*this->window);
}
