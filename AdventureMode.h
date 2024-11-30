#pragma once

#include "Camera.h"
#include "Collision.h"
#include "ColorManager.h"
#include "EntityFactory.h"
#include "Global.h"
#include "Map.h"
#include "PowerUp.h"
#include "Resources.h"
#include "Scene.h"

#include <vector>

class AdventureMode : public Scene
{
protected:
	// map objects
	std::vector<Entity*> entities;
	std::vector<Enemy*> enemies;
	Player* player;
	Map* map;
	sf::Vector2f cameraOrigin;
	Camera camera;

	void initMap(std::string fileName);

public:
	AdventureMode();
	AdventureMode(std::string fileName, sf::Vector2f cameraOrigin);
	virtual ~AdventureMode();
	void setEnemiesBehaviors();
	void update(float deltaTime, bool& held) override;
	void updateEntities(float deltaTime);
	virtual void updateMap(float deltaTime);
	virtual void updateCollision();
	virtual void updateCamera(float deltaTime);
	void updateLastPosition();

	virtual void render(sf::RenderWindow& target) override;
	virtual GameState getNextScene() override;
};

