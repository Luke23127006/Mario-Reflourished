#pragma once
#include "Entity.h"
#include "Animation.h"
#include<cmath>
#include "PowerUp.h"




class FlyingNimbus : public PowerUp
{
private:

	/*sf::RenderTexture nimbusTexture;
	Animation  * nimbusAnimation;*/
	bool isAppearing;
	float appearTime;
	float elapsedTime;
	sf::Vector2f playerPosition;
public:
	
	FlyingNimbus(sf::Vector2f position);
	void getPlayerPosition(sf::Vector2f playerPosition);
	bool appearing();
	float getAppearTime();
	virtual ~FlyingNimbus();
	void appear(float dt);
	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;

};
