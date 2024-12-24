#pragma once
#include "Entity.h"







class WukongMagicRod : public Entity
{
private:
	float duration;
	float angle;
	sf::Vector2f direction;
	bool spanMode;
	bool shrinkMode;
	bool stopMode;
	float maxSpanTime;
public:
	WukongMagicRod(sf::Vector2f position, sf::Vector2f direction);
	virtual ~WukongMagicRod();
	bool isExpire();
	void setDirection(sf::Vector2f direction);
	void die() override;
	void collideWithTile(Tile* tile, Direction from) override;
	void collideWithEntity(Entity* entity, Direction& from) override;
	void span(float deltaTime);
	void stop(float deltTime);
	void shrink(float deltaTime);
	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;
};