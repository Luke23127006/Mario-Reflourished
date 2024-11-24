#pragma once

#include "Camera.h"
#include "Collision.h"
#include "ColorManager.h"
#include "EntityFactory.h"
#include "Global.h"
#include "Map.h"
#include "PowerUp.h"
#include "Resources.h"
#include "UserInterface.h"

#include <vector>

class AdventureMode : public Scene
{
private:
	// map objects
	std::vector<Entity*> entities;
	Player* player;
	Map* map;
	sf::Vector2f cameraOrigin;
	Camera camera;

	void initMap(std::string fileName);

public:
	AdventureMode(std::string fileName, sf::Vector2f cameraOrigin);
	virtual ~AdventureMode();

	void update(float deltaTime) override;
	void updateEntities(float deltaTime);
	void updateMap(float deltaTime);
	void updateCollision();
	void updateCamera(float deltaTime);
	void updateLastPosition();

	void render(sf::RenderWindow& target, bool& held) override;
	virtual GameState getNextScene() override;
};

