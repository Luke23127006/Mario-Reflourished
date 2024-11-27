#pragma once

#include "AdventureMode.h"

class EndlessMode : public AdventureMode
{
private:
	std::vector<Map*> maps;
	int numMap;
	float cameraPosition;
	float cameraSpeed;

	void initMaps();
public:
	EndlessMode();
	virtual ~EndlessMode();

	void addMap(std::string fileName);

	void updateMap(float deltaTime) override;
	void updateCollision() override;
	void updateCamera(float deltaTime) override;

	void render(sf::RenderWindow& target, bool& held) override;
};

