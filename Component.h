#pragma once
#include "Global.h"
#include "Entity.h"






class Component {
protected:
	Entity* owner;
	Entity* player;
	bool enabled = true;
public:
	Component(Entity* owner, Entity* player) : owner(owner), player(player)  {}
	const bool isEnabled() const;
	virtual void update(float deltaTime) = 0;
	virtual ~Component() = default;
};