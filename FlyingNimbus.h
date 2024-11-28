#pragma once
#include "Entity.h"
#include "Animation.h"
#include<cmath>





class FlyingNimbus : public Entity
{
private:
	float duration;
	/*sf::RenderTexture nimbusTexture;
	Animation  * nimbusAnimation;*/
	bool isAppearing;
	float appearTime;
	float elapsedTime;
	sf::Vector2f playerPosition;
public:
	
	FlyingNimbus(sf::Vector2f position);
	void getPlayerPosition(sf::Vector2f playerPosition);
	virtual ~FlyingNimbus();
	void appear(float dt);
	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;

};
