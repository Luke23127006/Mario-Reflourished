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
#include "Coin.h"

#include <vector>

class AdventureMode : public Scene
{
protected:
	// map objects
	std::vector<Entity*> entities;
	std::vector<Coin*> coins;

	Player* player;
	Map* map;
	sf::Vector2f cameraOrigin;
	Camera camera;
	GameState typeMap;
	void initMap(std::string fileName);
	void addEntitiesAndCoins(std::string fileName, sf::Vector2f cornerPosition);

public:
	AdventureMode();
	AdventureMode(std::string fileName, sf::Vector2f cameraOrigin);
	virtual ~AdventureMode();
	void setEnemiesBehaviors();

	void update(float deltaTime, bool& held) override;
	void updateEntities(float deltaTime);
	virtual void updateCoins(float deltaTime);
	virtual void updateMap(float deltaTime);
	virtual void updateCollision();
	virtual void updateCamera(float deltaTime);
	void updateLastPosition();

	virtual void render(sf::RenderWindow& target) override;
	virtual GameState getNextScene() override;
};

