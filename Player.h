#pragma once

#include "Animation.h"
#include "Entity.h"
#include "Global.h"
#include "PowerUp.h"
#include "Resources.h"
#include "Bullet.h"
#include "FlyingNimbus.h"
#include <vector>

class Player : public Entity
{
private:
	PlayerState playerState;

	float blinkTimer;
	float invicibleTimer;
	float jumpTimer;
	int coins;
	int lives;
	bool canShoot = true;
	bool isNimbusActive = false;
	FlyingNimbus* nimbus;
	std::vector<Animation*> animation;
	std::vector<float> powerUpDuration;

public:
	Player(sf::Vector2f size, sf::Vector2f position);
	virtual ~Player();
	void stopJumping();
	void die() override;
	void gainPowerUp(PowerUp& powerUp);
	const bool hasPowerUp(PowerUpType type) const;
	void addCoin();

	Bullet* shoot();
	
	void update(float deltaTime) override;
	void updateMovementNimbus(float deltaTime);
	void updateMovement(float deltaTime);
	void updateAnimation(float deltaTime);
	void updatePowerUps(float deltaTime);
	void render(sf::RenderTarget& target) override;
};