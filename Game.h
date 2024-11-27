#pragma once

#include "AdventureMode.h"
#include "ColorManager.h"
#include "Global.h"
#include "Login.h"
#include "Play.h"
#include "Scene.h"
#include "Resources.h"
#include "SelectLevel.h"
#include "Welcome.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Game
{
private:
	// Variables
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event ev;
	sf::Clock clock;

	// Mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u windowSize;
	// UI
	bool held;
	sf::RenderTexture renderTexture;
	GameState currentGameState;
	std::unique_ptr<Scene> currentScene;
	void changeScene(GameState nextScene);
	void applyToMainWindow();

	// Initializers
	void initVariables();
	void initWindow();

public:
	Game();
	virtual ~Game();

	// Event & Mouse
	void pollEvents();
	void updateMousePosition();

	// Accessors
	const bool running() const;

	// Update
	void update(float deltaTime);

	// Render
	void render();

	// Run
	void run();
};