#include "EntitiesObserver.h"

EntitiesObserver::EntitiesObserver(std::vector<Entity*>& entities) :
	entities(entities)
{
}

void EntitiesObserver::addEntity(Entity* entity)
{
	this->entities.push_back(entity);
}