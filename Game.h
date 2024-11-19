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
#include "Map.h"
#include "Camera.h"
#include "Collision.h"
#include "UserInterface.h"
#include "Welcome.h"
<<<<<<< HEAD
#include "Login.h"
#include "Camera.h"
#include "Play.h"
=======
>>>>>>> a4c7a06dd011335e9651239fc49e3cea5f2b1eda
#include "SelectLevel.h"
#include "Play.h"

class Game
{
private:
	// Variables
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event ev;
	Camera camera;
	sf::Clock clock;

	// Mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Game objects
	std::vector<Entity*> entities;
	Player* player;
	Map* map;

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
	void initMap(std::string fileName);
	void initEntities(std::string fileName);

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
	void updateEntities(float deltaTime);
	void updateCollision();
	void updateCamera(float deltaTime);
	void updateLastPosition();

	// Render
	void render();
	void renderEntities();
	void renderMap();

	// Run
	void run();
};