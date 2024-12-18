#include "FireBall.h"
#include<iostream>
#include "Collision.h"






FireBall::FireBall(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f direction)
	: Entity(sf::Vector2f(FIREBALL_WIDTH, FIREBALL_HEIGHT), position)
{

	this->velocity = sf::Vector2f(FIREBALL_SPEED, FIREBALL_SPEED);
	this->direction = direction;
	this->duration = 5.0f;
	this->angle = 0.f;
	this->canSpan = true;

}

FireBall::~FireBall()
{
}

bool FireBall::isExpire()
{
	return this->duration <= 0.f;
}

void FireBall::setDirection(sf::Vector2f direction)
{
	this->direction = direction;
}

void FireBall::die()
{
	this->enabled = false;
	this->dying = true;
	this->dieTimer = 0.25f;
}


void FireBall::collideWithTile(Tile* tile, Direction from)
{
	Entity::collideWithTile(tile, from);
	if (!tile->isSolid()) return;

	
}

void FireBall::collideWithEntity(Entity* entity, Direction& from)
{
	entity->Entity::collideWithEntity(dynamic_cast<Entity*>(this), from);
	entity->collideWithEntity(this, from);
}


void FireBall::span(float deltaTime)
{

	sf::Vector2f newSize = this->getSize() + sf::Vector2f(deltaTime * 30, deltaTime * 30);
	sf::Vector2f difference = newSize - this->getSize();
	sf::Vector2f newPosition = this->getPosition() - difference;
	Entity *predictObject = new Entity(newSize, newPosition);

	Collision::handle_entity_map(predictObject, &this->getMap());
	std::vector<bool> collisionDirections = predictObject->getCollisionDirections();
	for (auto a : collisionDirections)
	{
		std::cout << a << " ";
	}
	std::cout << std::endl;
	if (collisionDirections[0] || collisionDirections[3])
	{
		delete predictObject;
		return;
	}
	else
	{
		this->setSize(newSize);
		this->setPosition(newPosition);
	}
	delete predictObject;

}

void FireBall::update(float deltaTime)
{
	if (!this->dying)
	{
		this->duration -= deltaTime;
	
		if (this->duration <= 0.f) this->die();
		this->span(deltaTime);
		this->velocity = this->direction * FIREBALL_SPEED;
		this->move(this->velocity * deltaTime);


	}
	else
	{
		this->dieTimer = std::max(0.f, this->dieTimer - deltaTime);
	}
}

void FireBall::render(sf::RenderTarget& target)
{
	Object::render(target);
	// Animation later

}


