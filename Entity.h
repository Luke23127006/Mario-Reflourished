#pragma once

#include "Global.h"
#include "Object.h"
#include "Animation.h"
#include "TileFactory.h"
class Map;
class Player;
class Enemy;
class Bullet;
class Shell;
class PowerUp;
class FireBall;
class WukongMagicRod;
class Entity : public Object
{
private:
	sf::Vector2f lastPosition;

protected:
	sf::Vector2f velocity;

	int health = 1;
	bool onGround;
	bool flipped;
	float dieTimer;
	bool dying;
	bool underWater;
	bool isColliding;
	std::vector<bool> collisionDirections; // 0: top, 1: right, 2: bottom, 3: left
	std::vector<Entity*>* thisWorld; // help each entity can access to the world easier
	Map* worldMap;
	std::vector<Animation*> animations;

public:
	Entity(sf::Vector2f size, sf::Vector2f position);
	virtual ~Entity();

	const bool isDead() const;
	const bool isDying() const;
	const bool isUnderWater() const;
	const bool isFlipped() const;
	sf::RectangleShape& getHitbox();
	void setOnGround(bool onGround);
	void setUnderWater(bool underWater);
	void setVelocity(sf::Vector2f velocity);
	void setSize(sf::Vector2f size);
	bool isCollide();
	void setCollide(bool isCollide);
	std::vector<bool>& getCollisionDirections();
	const bool getOnGround() const;
	const sf::Vector2f getVelocity() const;
	sf::Vector2f getLastPosition();

	void jump();
	void move(sf::Vector2f distance);
	// For ENTITY in WORLD
	void setAddressOfWorld(std::vector<Entity*>& world);
	std::vector<Entity*>& getWorld();
	void addEntity(Entity* entity);

	// For MAP in WORLD
	void setMap(Map* map);
	Map& getMap();
	
	// collision with tiles
	void collideWithTile(Tile* tile);
	virtual void collideWithTile(Tile* tile, Direction from);
	virtual void collideWithTile(LuckyBlock* luckyBlock, Direction from);
	virtual void collideWithTile(Portal* portal, Direction from);
	virtual void collideWithTile(Lava* lava, Direction from);
	virtual void collideWithTile(Water* water, Direction from);
	virtual void collideWithTile(VICTORYBlock * victory, Direction from);
	// collision with other entities
	virtual void collideWithEntity(Entity* other, Direction& from);
	virtual void collideWithEntity(Player* player, Direction from);
	virtual void collideWithEntity(Enemy* enemy, Direction from);
	virtual void collideWithEntity(Bullet* bullet, Direction from);
	virtual void collideWithEntity(FireBall* fireBall, Direction from);
	virtual void collideWithEntity(WukongMagicRod* wukongMagicRod, Direction from);
	virtual void collideWithEntity(Shell* shell, Direction from);
	virtual void collideWithEntity(PowerUp* powerUp, Direction from);
	
	sf::Vector2f getSize();
	virtual void die();

	virtual void update(float deltaTime) override;
	void updateLastPosition();

	virtual void render(sf::RenderTarget& target) override;
};
