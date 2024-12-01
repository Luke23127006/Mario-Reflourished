#pragma once

#include "Observer.h"
#include "Entity.h"

class EntitiesObserver : public Observer
{
private:
	std::vector<Entity*>& entities;
public:
	EntitiesObserver(std::vector<Entity*>& entities);
	virtual ~EntitiesObserver() = default;

	void addEntity(Entity* entity);
};

