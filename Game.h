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

class Game
{
private:
	// Variables
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event ev;
	GameState gameState;
	Camera camera;

	// Mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Game objects
	std::vector<Entity*> entities;
	Player* player;
	Map* map;

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
};

