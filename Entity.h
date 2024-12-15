#pragma once

#include "Global.h"
#include "Object.h"
#include "Animation.h"
#include "TileFactory.h"

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

	void collisionTile(Tile* tile);
	virtual void collisionTile(Tile* tile, Direction from);
	virtual void collisionTile(LuckyBlock* luckyBlock, Direction from);
	virtual void collisionTile(Portal* portal, Direction from);
	virtual void collisionTile(Lava* lava, Direction from);


	sf::Vector2f getLastPosition();
	sf::Vector2f getVelocity();
	virtual void die();

	virtual void update(float deltaTime) override;
	void updateLastPosition();

	virtual void render(sf::RenderTarget& target) override;
};
