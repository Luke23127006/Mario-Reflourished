#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Global.h"
#include "Resources.h"
#include "Entity.h"
#include "Player.h"
#include "Object.h"

class Game
{
private:
	// Variables
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event ev;
	GameState gameState;

	// Mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Game objects
	std::vector<Entity*> entities;

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
	void renderEntities();
};

