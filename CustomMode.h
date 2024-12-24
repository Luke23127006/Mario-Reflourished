#pragma once

#include "Scene.h"
#include "Player.h"
#include "TileFactory.h"
#include "Map.h"
#include "Collision.h"
#include "Camera.h"
#include <vector>

class CustomMode : public Scene
{
private:
	Player* player;
	//std::vector<Entity*> entities;
	Camera camera;

	//Map* map;

public:
	CustomMode();
	~CustomMode();
	
	void update(float deltaTime);
	void render(sf::RenderWindow& window) override;
	GameState getNextScene() override;
};

