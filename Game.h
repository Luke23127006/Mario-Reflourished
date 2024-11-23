#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Global.h"
#include "Resources.h"
#include "Entity.h"
#include "Player.h"
#include "Object.h"
#include "Map.h"
#include "Camera.h"
#include "Collision.h"
#include "UserInterface.h"
#include "Welcome.h"
#include "SelectLevel.h"
#include "Login.h"
#include "Play.h"
#include "AdventureMode.h"

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