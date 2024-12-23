#pragma once
#include "Camera.h"
#include "AdventureMode.h"
#include "EndlessMode.h"
#include "ColorManager.h"
#include "Global.h"
#include "Login.h"
#include "Play.h"
#include "Scene.h"
#include "Resources.h"
#include "SelectLevel.h"
#include "SelectCharacter.h"
#include "Welcome.h"
#include "Pause.h"
#include "HUD.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <stack>

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
	Camera camera;
	// UI
	bool held;
	sf::RenderTexture renderTexture;
	GameState currentGameState;
	std::vector<std::pair<std::unique_ptr<Scene>, bool >> states;
	std::unique_ptr<Scene> currentScene;
	void changeScene(GameState nextScene);
	void applyToMainWindow();

	// Initializers
	void initVariables();
	void initWindow();

public:
	Game();
	virtual ~Game();
	void pushState(std::unique_ptr<Scene> state, bool isOverlay);
	void popState();
	void clearState();
	// Event & Mouse
	void pollEvents();
	void updateMousePosition();

	void update(float deltaTime);
	void render();

	void run();
};