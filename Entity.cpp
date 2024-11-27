#include "Entity.h"

Entity::Entity(sf::Vector2f size, sf::Vector2f position) :
	Object(size, position),
	onGround(false),
	flipped(false),
	dieTimer(0.f),
	dying(false),
	lastPosition(position - sf::Vector2f(0, 1))
{
}

Entity::~Entity()
{
}

const bool Entity::isDead() const
{
	return this->dying && this->dieTimer <= 0;
}

const bool Entity::isDying() const
{
	return this->dying;
}

void Entity::setOnGround(bool onGround)
{
	this->onGround = onGround;
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

void Entity::jump()
{
	if (this->onGround)
	{
		this->velocity.y = -ENTITY_JUMP_STRENGHT;
		this->hitbox.move(sf::Vector2f(0.f, -0.01f));
		this->onGround = false;
	}
}

sf::Vector2f Entity::getLastPosition()
{
	return this->lastPosition;
}

sf::Vector2f Entity::getVelocity()
{
	return this->velocity;
}

void Entity::die()
{
	this->dying = true;
	this->enabled = false;
	this->dieTimer = 0.f;
}

void Entity::update(float deltaTime)
{
}

void Entity::updateLastPosition()
{
	this->lastPosition = this->hitbox.getPosition();
}
