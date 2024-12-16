#pragma once

#include "Global.h"
#include "Object.h"
#include "Animation.h"
#include "TileFactory.h"

class Player;
class Enemy;
class Bullet;
class Shell;
class PowerUp;

class Entity : public Object
{
private:
	sf::Vector2f lastPosition;

protected:
	sf::Vector2f velocity;

	bool onGround;
	bool flipped;
	float dieTimer;
	bool dying;
	bool underWater;

	std::vector<Animation*> animations;

public:
	Entity(sf::Vector2f size, sf::Vector2f position);
	virtual ~Entity();

	const bool isDead() const;
	const bool isDying() const;
	const bool isUnderWater() const;

	void setOnGround(bool onGround);
	void setUnderWater(bool underWater);
	void setVelocity(sf::Vector2f velocity);
	void jump();
	void move(sf::Vector2f distance);
	
	// collision with tiles
	void collisionTile(Tile* tile);
	virtual void collisionTile(Tile* tile, Direction from);
	virtual void collisionTile(LuckyBlock* luckyBlock, Direction from);
	virtual void collisionTile(Portal* portal, Direction from);
	virtual void collisionTile(Lava* lava, Direction from);
	virtual void collisionTile(Water* water, Direction from);

	// collision with other entities
	virtual void collisionEntity(Entity* other, Direction& from);
	virtual void collisionEntity(Player* player, Direction from);
	virtual void collisionEntity(Enemy* enemy, Direction from);
	virtual void collisionEntity(Bullet* bullet, Direction from);
	virtual void collisionEntity(Shell* shell, Direction from);
	virtual void collisionEntity(PowerUp* powerUp, Direction from);

	sf::Vector2f getLastPosition();
	sf::Vector2f getVelocity();
	virtual void die();

	virtual void update(float deltaTime) override;
	void updateLastPosition();

	virtual void render(sf::RenderTarget& target) override;
};
