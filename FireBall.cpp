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
	this->animations.push_back(new Animation(Resources::textures["FIREBALL"], 2, 0.2f, sf::Vector2i(50, 50)));
	this->animations[0]->setSize(sf::Vector2f(FIREBALL_WIDTH, FIREBALL_HEIGHT));


}

FireBall::~FireBall()
{
	for (auto *a : this->animations)
	{
		delete a;
	}
	this->animations.clear();
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
	if (from != Direction::NONE 
		&& dynamic_cast<Enemy*>(entity) != nullptr 
		&& !dynamic_cast<Bowser*> (entity)
		&& !dynamic_cast<Wukong*> (entity)
		)
	{
		entity->die();
	}
}


void FireBall::span(float deltaTime)
{

	sf::Vector2f newSize = this->getSize() + sf::Vector2f(deltaTime * 30, deltaTime * 30);
	sf::Vector2f difference = newSize - this->getSize();
	sf::Vector2f newPosition = this->getPosition() - difference;
	Entity *predictObject = new Entity(newSize, newPosition);

	Collision::handle_entity_map(predictObject, &this->getMap());
	std::vector<bool> collisionDirections = predictObject->getCollisionDirections();
	
	if (collisionDirections[0] || collisionDirections[3])
	{
		delete predictObject;
		return;
	}
	else
	{
		this->setSize(newSize);
		this->animations[0]->setSize(newSize);
		this->setPosition(newPosition);
	}
	delete predictObject;

}

void FireBall::update(float deltaTime)
{
	if (!this->dying)
	{
		for (auto & a : this->animations)
		{
			a->update(deltaTime, false);
		}
		this->duration -= deltaTime;
	
		if (this->duration <= 0.f) this->die();
		this->span(deltaTime);
		this->velocity = this->direction * FIREBALL_SPEED;
		this->animations[0]->setPosition(this->getPosition());
		this->move(this->velocity * deltaTime);


	}
	else
	{
		this->dieTimer = std::max(0.f, this->dieTimer - deltaTime);
	}
}

void FireBall::render(sf::RenderTarget& target)
{
	Entity::render(target);

}


