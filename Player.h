#pragma once

#include "Global.h"
#include "Entity.h"
#include "Animation.h"
#include "Resources.h"
#include <vector>

class Player : public Entity
{
private:
	PlayerState playerState;

	float invicibleTimer;
	int coins;
	int lives;

	std::vector<Animation*> animation;
	std::vector<float> powerUpDuration;

public:
	Player(sf::Vector2f size, sf::Vector2f position);
	virtual ~Player();

	void update(float deltaTime) override;
	void updateMovement(float deltaTime);
	void updateAnimation(float deltaTime);
	void render(sf::RenderTarget& target) override;
};