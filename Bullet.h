#pragma once

#include "Entity.h"

class Bullet : public Entity
{
private:
	float duration;
	float angle;
public:
	Bullet(sf::Vector2f position, sf::Vector2f velocity);
	virtual ~Bullet();

	void bounce();
	bool isExpired();

	void die() override;

	void collideWithTile(Tile* tile, Direction from) override;

	void collideWithEntity(Entity* entity, Direction& from) override;
	void collideWithEntity(Shell* shell, Direction from) override;

	void update(float deltaTime) override;

	void render(sf::RenderTarget& target) override;
};

