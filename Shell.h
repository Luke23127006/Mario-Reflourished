#pragma once

#include "Entity.h"
#include "Global.h"
#include "Resources.h"
#include "Player.h"

class Shell : public Entity
{
private:
	bool activated;
public:
	Shell(sf::Vector2f position);
	virtual ~Shell();

	const bool isActivated() const;
	void switchActivation();
	void turnAround();

	void collideWithTile(Tile* tile, Direction from) override;

	void collideWithEntity(Entity* entity, Direction& from) override;

	void update(float deltaTime) override;
};

