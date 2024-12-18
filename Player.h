#pragma once

#include "Animation.h"
#include "Entity.h"
#include "Global.h"
#include "PowerUp.h"
#include "Resources.h"
#include "Bullet.h"
#include "FlyingNimbus.h"
#include "Enemy.h"
#include "Shell.h"
#include "FireBall.h"
#include <vector>

class Player : public Entity
{
private:
	PlayerState playerState;
	std::vector<PowerUp*> powerUps;

	sf::Vector2f acceleration;

	bool canBreakBlocks = false;
	sf::Vector2f velocityMax;

	float blinkTimer;
	float invicibleTimer;
	float jumpTimer;
	float jumpTimerMax = PLAYER_JUMP_TIME;
	int coins;
	int lives;
	bool canShoot = true;
	bool isNimbusActive = false;

public:
	Player(sf::Vector2f size, sf::Vector2f position);
	virtual ~Player();
	void stopJumping();
	void takeDamage();
	void die() override;
	void gainPowerUp(PowerUp* powerUp);
	const bool hasPowerUp(PowerUpType type) const;
	void addCoin();

	sf::Vector2f getAcceleration();
	int getHealth();

	void setCanBreakBlocks(bool canBreakBlocks);
	void setVelocityMax(sf::Vector2f velocityMax);
	void setAcceleration(sf::Vector2f acceleration);
	void setHealth(int health);

	Bullet* shoot();

	void collideWithTile(Tile* tile, Direction from) override;
	void collideWithTile(LuckyBlock* tile, Direction from) override;
	void collideWithTile(Portal* tile, Direction from) override;

	void collideWithEntity(Enemy* enemy, Direction from) override;
	void collideWithEntity(Shell* shell, Direction from) override;
	void collideWithEntity(PowerUp* powerUp, Direction from) override;
	void collideWithEntity(FireBall* fireBall, Direction from) override;
	
	void update(float deltaTime) override;
	void updateAcceleration(float deltaTime);
	void updateMovement(float deltaTime);
	void updateAnimation(float deltaTime);
	void updatePowerUps(float deltaTime);
	void render(sf::RenderTarget& target) override;
};