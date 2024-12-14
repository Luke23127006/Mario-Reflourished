#pragma once

#include "AdventureMode.h"
#include "SpikeWall.h"

class EndlessMode : public AdventureMode
{
private:
	std::vector<Map*> maps;
	SpikeWall* spikeWall;
	int numMap;
	float cameraPosition;
	float gameSpeed;
	float spikeSpeed;
	float cameraHeightMax;

	void initMaps();
public:
	EndlessMode();
	virtual ~EndlessMode();

	void addMap(std::string fileName);
	
	void updateCoins(float deltaTime) override;
	void updateMap(float deltaTime) override;
	void updateCollision() override;
	void updateCamera(float deltaTime) override;

	void render(sf::RenderWindow& target) override;
	GameState getNextScene() override;
};

