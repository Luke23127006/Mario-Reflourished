#include "WukongMagicRod.h"
#include<iostream>
#include "Collision.h"






WukongMagicRod::WukongMagicRod(sf::Vector2f position, sf::Vector2f direction)
	: Entity(sf::Vector2f(MAGIC_ROD_WIDTH, MAGIC_ROD_HEIGHT), position)
{
	
	this->velocity = sf::Vector2f(0.f, 0.f);
	this->direction = direction;
	this->duration = 2.0f;
	this->maxSpanTime = 3.0f;
	this->angle = 0.f;
	this->spanMode = true;
	this->shrinkMode = false;
	this->stopMode = false;
	bool isReverse = false;
	this->animations.push_back(new Animation(Resources::textures["MAGIC_ROD"], 2, 0.2f, sf::Vector2i(310, 20)));
	this->animations[0]->setSize(sf::Vector2f(MAGIC_ROD_WIDTH, MAGIC_ROD_HEIGHT));
	if (direction.x < 0)
	{
		this->flipped = true;
		this->angle = 180.f;
	}
	else
	{
		this->flipped = false;
		
	}
	
	if (this->flipped)
	{
		
		this->animations[0]->setRotation(180.f);
		this->hitbox.setRotation(180.f);
		

	}
	
	//this->animations[0]->setScale(sf::Vector2f(MAGIC_ROD_WIDTH / 20, MAGIC_ROD_HEIGHT / 310));
	
}

WukongMagicRod::~WukongMagicRod()
{
	for (auto *a : this->animations)
	{
		delete a;
	}
	this->animations.clear();
}

bool WukongMagicRod::isExpire()
{
	return this->duration <= 0.f;
}

void WukongMagicRod::setDirection(sf::Vector2f direction)
{
	this->direction = direction;
}

void WukongMagicRod::die()
{
	this->enabled = false;
	this->dying = true;
	this->dieTimer = 0.25f;
}


void WukongMagicRod::collideWithTile(Tile* tile, Direction from)
{
	Entity::collideWithTile(tile, from);
	if (!tile->isSolid()) return;


}



void WukongMagicRod::collideWithEntity(Entity* entity, Direction& from)
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


void WukongMagicRod::span(float deltaTime)
{
	maxSpanTime -= deltaTime;
	if (maxSpanTime <= 0.f)
	{
		this->spanMode = false;
		this->stopMode = true;
		return;
	}
	sf::Vector2f newSize = this->getSize() + sf::Vector2f(deltaTime * 400, deltaTime * 12);
	
	Entity* predictObject = new Entity(newSize, this->getPosition());;
	if (flipped)
	{
		predictObject->getHitbox().setRotation(180.f);
		predictObject->setPosition(this->getPosition());
	}


	Collision::handle_entity_map(predictObject, &this->getMap());
	std::vector<bool> collisionDirections = predictObject->getCollisionDirections();
	if (collisionDirections[1] || collisionDirections[3])
	{
		
		this->spanMode = false;
		this->stopMode = true;
		delete predictObject;
		return;
	}
	else
	{
		sf::Vector2f newPosition;
		sf::Vector2f difference = newSize - this->getSize();
		if (collisionDirections[2] && !flipped)
		{
			newPosition = this->getPosition() - difference;
			this->setPosition(newPosition);
		}
		else if (collisionDirections[0] && flipped)
		{
			newPosition = this->getPosition() + difference;
			this->setPosition(newPosition);
		}
		//this->animations[0]->setScale(sf::Vector2f(newSize.x / this->getSize().x, newSize.y / this->getSize().y));
		this->animations[0]->setSize(newSize);
		this->setSize(newSize);
		
	}
	delete predictObject;

}

void WukongMagicRod::stop(float deltaTime)
{
	if (this->duration >= 0.5f)
	{
		this->duration -= deltaTime;
	}
	else
	{
		this->stopMode = false;
		this->shrinkMode = true;
	}
}
void WukongMagicRod::shrink(float deltaTime)
{
	sf::Vector2f newSize = this->getSize() - sf::Vector2f(deltaTime * 1000, deltaTime * 12);
	
	newSize.x = std::max(newSize.x, 1.f);
	newSize.y = std::max(newSize.y, 1.f);
	this->animations[0]->setSize(newSize);
	this->setSize(newSize);
	if (newSize.x <= 1.f || newSize.y <= 1.f)
	{
		this->die();
	}
}
void WukongMagicRod::update(float deltaTime)
{
	if (!this->dying)
	{
		for (auto& a : this->animations)
		{
			a->update(deltaTime, false);
			
			
		}
		if (spanMode)
		{
			this->span(deltaTime);
		}
		else if (stopMode)
		{
			this->stop(deltaTime);
		}
		else if (shrinkMode)
		{
			this->shrink(deltaTime);
		}

	}
	else
	{
		this->dieTimer = std::max(0.f, this->dieTimer - deltaTime);
	}
}

void WukongMagicRod::render(sf::RenderTarget& target)
{

	// Animation later

	Entity::render(target);



}


