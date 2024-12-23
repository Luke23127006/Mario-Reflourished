#include "Game.h"

void Game::changeScene(GameState nextScene)
{



	if (this->currentGameState == nextScene) return;

	switch (nextScene)
	{
	case GameState::WELCOME:

		clearState();
		pushState(std::make_unique<Welcome>(this->renderTexture), false);
		this->currentGameState = GameState::WELCOME;
		break;
	case GameState::LOGIN:
		
		clearState();
		pushState(std::make_unique<Login>(renderTexture), false);
		this->currentGameState = GameState::LOGIN;
		break;
	case GameState::PLAY:
		
		clearState();
		pushState(std::make_unique<Play>(this->renderTexture), false);
		this->currentGameState = GameState::PLAY;
		break;
	case GameState::SELECT_LEVEL:
		
		clearState();
		pushState(std::make_unique<SelectLevel>(this->renderTexture), false);
		this->currentGameState = GameState::SELECT_LEVEL;
		break;
	case GameState::SELECT_CHARACTER:
		clearState();
		pushState(std::make_unique<SelectCharacter>(this->renderTexture), false);
		this->currentGameState = GameState::SELECT_CHARACTER;
		break;
	case GameState::LEVEL1:
		
		std::cout << "Level1\n";
		clearState();
		pushState(std::make_unique<AdventureMode>(MAPS_DIRECTORY + "Level 1.png", sf::Vector2f(0.1f * this->window->getSize().x, 0)), false);
		pushState(std::make_unique<HUD>(this->renderTexture, false), true);
		this->currentGameState = GameState::LEVEL1;
		break;
	case GameState::LEVEL2:
		
		std::cout << "Level2\n";
		clearState();
		pushState(std::make_unique<AdventureMode>(MAPS_DIRECTORY + "Level 2.png", sf::Vector2f(0, 0)), false);
		pushState(std::make_unique<HUD>(this->renderTexture, false), true);
		this->currentGameState = GameState::LEVEL2;
		break;
	case GameState::LEVEL3:
		
		std::cout << "Level3\n";
		clearState();
		pushState(std::make_unique<EndlessMode>(), false);
		pushState(std::make_unique<HUD>(this->renderTexture, true), true);
		this->currentGameState = GameState::LEVEL3;
		break;
	case GameState::PAUSE:
		Resources::textures["Pause Background"].create(this->window->getSize().x, this->window->getSize().y);
		Resources::textures["Pause Background"].update(*this->window);
		Resources::textures["Pause Background"].setRepeated(true);
		pushState(std::make_unique<Pause>(this->renderTexture), false);
		this->currentGameState = GameState::PAUSE;
		break;
	case GameState::RESUME:
		std::cout << "Resume\n";
		popState();
		for (auto it = this->states.rbegin(); it != this->states.rend(); it++)
		{
			if (!it->second)
			{
				this->currentGameState = it->first->getNextScene();
				break;
			}
		}
		break;

	case GameState::REPLAY:
		std::cout << "Replay\n";
		popState();
		this->currentGameState = GameState::REPLAY;
		break;
	case GameState::EXIT:

		this->window->close();
		break;

	default:
		break;
	}
	this->applyToMainWindow();
}

void Game::applyToMainWindow()
{
	// Create a sprite to hold the render texture
	sf::Sprite sprite(this->renderTexture.getTexture());

	// Clear the main window and draw the sprite (containing the off-screen rendered content)
	this->window->clear();
	this->window->draw(sprite);
}

void Game::pushState(std::unique_ptr<Scene> state, bool isOverlay)
{
	this->states.push_back(std::make_pair(std::move(state), isOverlay));
}

void Game::popState()
{
	if (!this->states.empty())
	{
		this->states.pop_back();
	}
}


void Game::clearState()
{
	while (!this->states.empty())
	{
		this->states.pop_back();
	}
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

	pushState(std::make_unique<Welcome>(this->renderTexture), false);
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
	this->windowSize = this->window->getSize();
	WINDOW_SIZE = this->windowSize;
	MOUSE_POSITION = this->mousePosWindow;
	MOUSE_VIEW_POSITION = this->mousePosView;
}

void Game::update(float deltaTime)
{
	this->pollEvents();
	this->updateMousePosition();
	//this->states.top()->update(deltaTime, held);
	// Update main scene
	GameState nextScene = GameState::NONE;
	for (auto it = this->states.rbegin(); it != this->states.rend(); it++)
	{
		if (it->second)
		{
			it->first->update(deltaTime, held);
		}
		if (!it->second)
		{
			nextScene = it->first->getNextScene();
			it->first->update(deltaTime, held);
			break;
		}
		
	}
	this->changeScene(nextScene);


	
}

void Game::render()
{
	this->window->clear(sf::Color::White);
	//this->window->setView(this->window->getDefaultView());
	this->window->setView(this->camera.getView(this->window->getSize()));
	//this->states.top()->render(*this->window);
	
	// Update main scene
	for (auto it = this->states.rbegin(); it != this->states.rend(); it++)
	{
		if (!it->second)
		{
			it->first->render(*this->window);
			break;
		}

	}

	if (this->states.rbegin()->second)
	{
		this->states.rbegin()->first->render(*this->window);
	}

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
