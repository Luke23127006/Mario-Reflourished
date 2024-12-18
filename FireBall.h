#pragma once
#include "Entity.h"







class FireBall : public Entity {
private:
	float duration;
	float angle;
	sf::Vector2f direction;
	bool canSpan;
public:
	FireBall(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f direction);
	virtual ~FireBall();
	bool isExpire();
	void setDirection(sf::Vector2f direction);
	void die() override;
	void collideWithTile(Tile* tile, Direction from) override;
	void collideWithEntity(Entity* entity, Direction& from) override;
	void span(float deltaTime);
	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;
};