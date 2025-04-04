﻿#include "Game.h"

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

	case GameState::HISTORY:
		clearState();
		pushState(std::make_unique<History>(this->renderTexture), false);
		this->currentGameState = GameState::HISTORY;
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
		Resources::sounds[currentMusic].pause();
		Resources::textures["Pause Background"].create(this->window->getSize().x, this->window->getSize().y);
		Resources::textures["Pause Background"].update(*this->window);
		Resources::textures["Pause Background"].setRepeated(true);
		pushState(std::make_unique<Pause>(this->renderTexture), false);
		this->currentGameState = GameState::PAUSE;
		break;
	case GameState::RESUME:
		std::cout << "Resume\n";
		std::cout << "Before " << states.size() << std::endl;
		//if (currentGameState == GameState::PAUSE) popState();
		//std::cout << "After " << states.size() << std::endl;
		if (this->currentGameState == GameState::PAUSE) popState();
		Resources::sounds[currentMusic].play();
		Resources::sounds[currentMusic].setLoop(true);
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
		if (currentMusic == "MARIO_WATER")
		{
			Resources::sounds[currentMusic].stop();
			Resources::sounds[prevMusic].play();
			Resources::sounds[prevMusic].setLoop(true);
			currentMusic = prevMusic;
		}
		else
		{
			Resources::sounds[currentMusic].stop();
			Resources::sounds[currentMusic].play();
			Resources::sounds[currentMusic].setLoop(true);
		}
		this->currentGameState = GameState::REPLAY;
		break;
	case GameState::VICTORY:
		std::cout << "Victory\n";
		std::cout << SCORE << std::endl;
		clearState();
		std::cout << SCORE << std::endl;
		if (currentGameState == GameState::LEVEL1)
			pushState(std::make_unique<VictoryScene>(this->renderTexture, "LEVEL 1"), false);
		else if (currentGameState == GameState::LEVEL2)
			pushState(std::make_unique<VictoryScene>(this->renderTexture, "LEVEL 2"), false);
		else if (currentGameState == GameState::LEVEL3)
			pushState(std::make_unique<VictoryScene>(this->renderTexture, "LEVEL 3"), false);
		
		
		this->currentGameState = GameState::VICTORY;
		break;
	case GameState::EXIT:

		Resources::sounds[currentMusic].stop();
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
			// Handle key presses here if needed
			break;

		case sf::Event::Resized:
		{
			const float minAspect = 1.5f;
			const float maxAspect = 2.0f;

			float width = static_cast<float>(this->ev.size.width);
			float height = static_cast<float>(this->ev.size.height);

			float aspect = width / height;

			if (aspect < minAspect) {
				width = height * minAspect;
			}
			else if (aspect > maxAspect) {
				width = height * maxAspect;
			}

			this->window->setSize(sf::Vector2u(static_cast<unsigned int>(width), static_cast<unsigned int>(height)));
			break;
		}

		case sf::Event::MouseWheelScrolled:
		{
			if (this->ev.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
				if (this->ev.mouseWheelScroll.delta > 0) {
					ZOOM_LEVEL *= 0.9f; // Zoom in
				}
				else if (this->ev.mouseWheelScroll.delta < 0) {
					ZOOM_LEVEL *= 1.1f; // Zoom out
				}

				ZOOM_LEVEL = std::min(std::max(1.f * ZOOM_LEVEL, 480.0f), 1120.f);

				sf::View view = this->window->getView();
				view.setSize(this->window->getDefaultView().getSize());
				view.zoom(ZOOM_LEVEL / 720.0f); // Apply zoom relative to 720 as base
				this->window->setView(view);
			}

			RENDER_DISTANCE = ZOOM_LEVEL + 100.f;
			UPDATE_DISTANCE = RENDER_DISTANCE + 300.f;
			break;
		}

		case sf::Event::MouseButtonPressed:
		{
			if (this->ev.mouseButton.button == sf::Mouse::Middle) {
				ZOOM_LEVEL = 720.0f; // Reset zoom level to 720

				sf::View view = this->window->getView();
				view.setSize(this->window->getDefaultView().getSize());
				view.zoom(ZOOM_LEVEL / 720.0f); // Reset view to default scale
				this->window->setView(view);
			}
			RENDER_DISTANCE = ZOOM_LEVEL + 100.f;
			UPDATE_DISTANCE = RENDER_DISTANCE + 300.f;
			break;
		}

		default:
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


	this->changeScene(nextScene);
}

void Game::render()
{
	this->window->clear(sf::Color(187, 222, 251));
	this->window->setView(this->window->getDefaultView());
	//this->window->setView(this->camera.getView(this->window->getSize()));
	
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
