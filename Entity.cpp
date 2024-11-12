#include "Entity.h"

Entity::Entity(sf::Vector2f size, sf::Vector2f position) :
	Object(size, position),
	onGround(false),
	flipped(false),
	dead(false)
{
}

Entity::~Entity()
{
}

void Entity::setOnGround(bool onGround)
{
	this->onGround = onGround;
}

void Entity::die()
{
	this->dead = true;
}

void Entity::update(float deltaTime)
{
}

void Entity::updateLastPosition()
{
	this->lastPosition = this->hitbox.getPosition();
}
