#include "Game.h"

void Game::changeScene(GameState nextScene)
{





	if (this->currentGameState == nextScene) return;

	switch (nextScene)
	{
	case GameState::WELCOME:
		

		/*this->currentScene = std::make_unique<Welcome>(this->renderTexture);*/
		popState();
		pushState(std::make_unique<Welcome>(this->renderTexture));
		this->currentGameState = GameState::WELCOME;
		break;
	case GameState::LOGIN:
		
		popState();
		pushState(std::make_unique<Login>(renderTexture));
		this->currentGameState = GameState::LOGIN;
		break;
	case GameState::PLAY:
		
		std::cout << "Play\n";
		if (this->currentGameState == GameState::PAUSE)
		{
			clearState();
		}
		pushState(std::make_unique<Play>(this->renderTexture));
		this->currentGameState = GameState::PLAY;
		break;
	case GameState::SELECT_LEVEL:
		
		std::cout << "SelectLevel\n";
		popState();
		pushState(std::make_unique<SelectLevel>(this->renderTexture));
		this->currentGameState = GameState::SELECT_LEVEL;
		break;
	case GameState::LEVEL1:
		
		std::cout << "Level1\n";
		if (this->currentGameState == GameState::REPLAY)
		{
			std::cout << "Hereeeeeeeeeeeeeeee\n";
		}
		clearState();
		pushState(std::make_unique<AdventureMode>(MAPS_DIRECTORY + "Level 1.png", sf::Vector2f(0.1f * this->window->getSize().x, 0)));
		//this->currentScene = std::make_unique<AdventureMode>(MAPS_DIRECTORY + "demo_map.png", sf::Vector2f(0.1f * this->window->getSize().x, 0));
		this->currentGameState = GameState::LEVEL1;
		break;
	case GameState::LEVEL2:
		
		std::cout << "Level2\n";
		if (this->currentGameState == GameState::RESUME)
		{
			this->currentGameState = GameState::LEVEL2;
			break;
		}
		clearState();
		pushState(std::make_unique<AdventureMode>(MAPS_DIRECTORY + "Level 2.png", sf::Vector2f(0, 0)));
		this->currentGameState = GameState::LEVEL2;
		break;
	case GameState::LEVEL3:
		
		std::cout << "Level3\n";
		if (this->currentGameState == GameState::RESUME)
		{
			this->currentGameState = GameState::LEVEL3;
			break;
		}
		clearState();
		pushState(std::make_unique<EndlessMode>());
		this->currentGameState = GameState::LEVEL3;
		break;
	case GameState::PAUSE:
		Resources::textures["Pause Background"].create(this->window->getSize().x, this->window->getSize().y);
		Resources::textures["Pause Background"].update(*this->window);
		Resources::textures["Pause Background"].setRepeated(true);
		
		
	
		pushState(std::make_unique<Pause>(this->renderTexture));
		this->currentGameState = GameState::PAUSE;
		break;
	case GameState::RESUME:
		std::cout << "Resume\n";
		popState();
		this->currentGameState = states.top()->getNextScene();
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

void Game::pushState(std::unique_ptr<Scene> state)
{
	this->states.push(std::move(state));
}

void Game::popState()
{
	if (!this->states.empty())
	{
		this->states.pop();
	}
}


void Game::clearState()
{
	while (!this->states.empty())
	{
		this->states.pop();
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

	pushState(std::make_unique<Welcome>(this->renderTexture));
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
	this->states.top()->update(deltaTime, held);
	this->changeScene(this->states.top()->getNextScene());
}

void Game::render()
{
	this->window->clear(sf::Color::White);
	//this->window->setView(this->window->getDefaultView());
	this->window->setView(this->camera.getView(this->window->getSize()));
	this->states.top()->render(*this->window);
}

void Game::run()
{
	while (this->window->isOpen())
	{
		float deltaTime = this->clock.restart().asSeconds();

		float FPS = 1 / deltaTime;
		if (FPS < 60.f) continue;

		this->update(deltaTime);
		this->render();
		this->window->display();
	}
}
