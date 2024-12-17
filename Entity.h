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
	void collideWithTile(Tile* tile);
	virtual void collideWithTile(Tile& tile, Direction from);
	virtual void collideWithTile(LuckyBlock& luckyBlock, Direction from);
	virtual void collideWithTile(Portal& portal, Direction from);
	virtual void collideWithTile(Lava& lava, Direction from);
	virtual void collideWithTile(Water& water, Direction from);

	// collision with other entities
	virtual void collideWithEntity(Entity* other, Direction& from);
	virtual void collideWithEntity(Player* player, Direction from);
	virtual void collideWithEntity(Enemy* enemy, Direction from);
	virtual void collideWithEntity(Bullet* bullet, Direction from);
	virtual void collideWithEntity(Shell* shell, Direction from);
	virtual void collideWithEntity(PowerUp* powerUp, Direction from);

	sf::Vector2f getLastPosition();
	sf::Vector2f getVelocity();
	virtual void die();

	virtual void update(float deltaTime) override;
	void updateLastPosition();

	virtual void render(sf::RenderTarget& target) override;
};