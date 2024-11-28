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
	float cameraSpeed;
	float cameraHeightMax;

	void initMaps();
public:
	EndlessMode();
	virtual ~EndlessMode();

	void addMap(std::string fileName);

	void updateMap(float deltaTime) override;
	void updateCollision() override;
	void updateCamera(float deltaTime) override;

	void render(sf::RenderWindow& target) override;
};

