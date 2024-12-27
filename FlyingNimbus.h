#pragma once
#include "Entity.h"
#include "Animation.h"
#include <cmath>
#include "PowerUp.h"




class FlyingNimbus : public PowerUp
{
private:
	bool isAppearing;
	float appearTime;
	float elapsedTime;
public:
	FlyingNimbus(Player* player);
	virtual ~FlyingNimbus();

	void appear(float deltaTime);
	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;

	void applyPowerUp(float deltaTime) override;
};
