#include "Entity.h"
#include <iostream>
Entity::Entity(sf::Vector2f size, sf::Vector2f position) :
	Object(size, position),
	onGround(false),
	flipped(false),
	dieTimer(0.f),
	dying(false),
	underWater(false),
	lastPosition(position - sf::Vector2f(0, 0.001))
{
	sf::Color color = this->hitbox.getFillColor();
	color.a = 128;
	this->hitbox.setFillColor(color);
	this->collisionDirections = std::vector<bool>(4, false);
	this->isColliding = false;
	this->thisWorld = nullptr;
	this->worldMap = nullptr;

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

const bool Entity::isUnderWater() const
{
	return this->underWater;
}

void Entity::setOnGround(bool onGround)
{
	this->onGround = onGround;
}

void Entity::setUnderWater(bool underWater)
{
	this->underWater = underWater;
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

void Entity::setSize(sf::Vector2f size)
{
	this->hitbox.setSize(size);
}

bool Entity::isCollide()
{
	return this->isColliding;
}

// FOR CURRENT ENTITY WORLD
void Entity::setAddressOfWorld(std::vector<Entity*>& world)
{
	thisWorld = &world;
}

std::vector<Entity*>& Entity::getWorld()
{
	return *thisWorld;
}
void Entity::addEntity(Entity* entity)
{
	thisWorld->push_back(entity);
}

// FOR CURRENT ENTITY MAP

void Entity::setMap(Map* map)
{

	worldMap = map;
}

Map& Entity::getMap()
{
	return *worldMap;
}

const bool Entity::getOnGround() const
{
	return this->onGround;
}

const sf::Vector2f Entity::getVelocity() const
{
	return this->velocity;
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

void Entity::move(sf::Vector2f distance)
{
	if (this->underWater)
	{
		this->hitbox.move(distance * 0.5f);
	}
	else
	{
		this->hitbox.move(distance);
	}
}

std::vector<bool>& Entity::getCollisionDirections()
{
	return this->collisionDirections;
}

void Entity::collideWithTile(Tile* tile)
{
	Direction from = Direction::NONE;

	if (this->dying) return;

	Entity* entity = this;
	sf::FloatRect entityBounds = entity->getGlobalBounds();
	sf::Vector2f lastPosition = entity->getLastPosition();
	sf::FloatRect tileBounds = tile->getGlobalBounds();

	bool above = checkAbove(entityBounds, lastPosition, tileBounds);
	bool below = checkBelow(entityBounds, lastPosition, tileBounds);

	// Entity in ON GROUND
	if (checkOnGround(entityBounds, tileBounds) && tile->isSolid())
	{
		entity->setOnGround(true);
	}

	// Entity in INTERSECT with TILE
	if (entityBounds.intersects(tileBounds))
	{
		isColliding = true;
		if (tile->isDanger())
		{
			entity->die();
		}
		else if (above)
		{
			from = Direction::UP;
			collisionDirections[0] = true;
		}
		else if (below)
		{
			from = Direction::DOWN;
			collisionDirections[2] = true;
		}
		else
		{
			// PLAYER
			if (entityBounds.left <= tileBounds.left)
			{
				from = Direction::LEFT;
				collisionDirections[3] = true;
			}
			else if (entityBounds.left > tileBounds.left)
			{
				from = Direction::RIGHT;
				collisionDirections[1] = true;
			}
		}
	}
	else
	{
		isColliding = false;
	}

	entity->collideWithTile(tile, from);
}

void Entity::collideWithTile(Tile* tile, Direction from)
{
	sf::FloatRect tileBounds = tile->getGlobalBounds();
	sf::FloatRect entityBounds = this->getGlobalBounds();

	if (tile->isSolid())
	{
		switch (from)
		{
		case Direction::UP:
			this->onGround = true;
			this->velocity.y = 0.f;
			this->setPosition(sf::Vector2f(entityBounds.left, tileBounds.top - entityBounds.height));
			break;
		case Direction::DOWN:
			this->velocity.y = 0.f;
			this->setPosition(sf::Vector2f(entityBounds.left, tileBounds.top + tileBounds.height));
			break;
		case Direction::LEFT:
			this->setPosition(sf::Vector2f(tileBounds.left - entityBounds.width, entityBounds.top));
			break;
		case Direction::RIGHT:
			this->setPosition(sf::Vector2f(tileBounds.left + tileBounds.width, entityBounds.top));
			break;
		default:
			return;
		}
	}

	if (from == Direction::NONE) return;
	if (isType<Portal>(*tile))
	{
		this->collideWithTile(dynamic_cast<Portal*>(tile), from);
	}
	if (isType<LuckyBlock>(*tile))
	{
		this->collideWithTile(dynamic_cast<LuckyBlock*>(tile), from);
	}
	if (isType<Lava>(*tile))
	{
		this->collideWithTile(dynamic_cast<Lava*>(tile), from);
	}
	if (isType<Water>(*tile))
	{
		this->collideWithTile(dynamic_cast<Water*>(tile), from);
	}
}

void Entity::collideWithTile(LuckyBlock* luckyBlock, Direction from)
{
}

void Entity::collideWithTile(Portal* portal, Direction from)
{
}

void Entity::collideWithTile(Lava* lava, Direction from)
{
	this->die();
}

void Entity::collideWithTile(Water* water, Direction from)
{
	this->underWater = true;
}

void Entity::collideWithEntity(Entity* other, Direction& from)
{
	from = Direction::NONE;

	Entity* entity = this;
	sf::FloatRect entityBounds = entity->getGlobalBounds();
	sf::Vector2f lastPosition = entity->getLastPosition();
	sf::FloatRect tileBounds = other->getGlobalBounds();

	bool above = checkAbove(entityBounds, lastPosition, tileBounds);
	bool below = checkBelow(entityBounds, lastPosition, tileBounds);

	// Entity in ON GROUND
	if (checkOnGround(entityBounds, tileBounds))
	{
		entity->setOnGround(true);
	}

	if (entityBounds.intersects(tileBounds))
	{
		if (above)
		{
			from = Direction::UP;
		}
		else if (below)
		{
			from = Direction::DOWN;
		}
		else
		{
			if (entityBounds.left <= tileBounds.left)
			{
				from = Direction::LEFT;
			}
			else if (entityBounds.left > tileBounds.left)
			{
				from = Direction::RIGHT;
			}
		}
	}
}

void Entity::collideWithEntity(Player* player, Direction from)
{
}

void Entity::collideWithEntity(Enemy* enemy, Direction from)
{
}

void Entity::collideWithEntity(Bullet* bullet, Direction from)
{
}

void Entity::collideWithEntity(FireBall* fireBall, Direction from)
{
}
void Entity::collideWithEntity(Shell* shell, Direction from)
{
}

void Entity::collideWithEntity(PowerUp* powerUp, Direction from)
{
}

sf::Vector2f Entity::getLastPosition()
{
	return this->lastPosition;
}

sf::Vector2f Entity::getVelocity()
{
	return this->velocity;
}

sf::Vector2f Entity::getSize()
{
	return this->hitbox.getSize();
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

void Entity::render(sf::RenderTarget& target)
{
	Object::render(target);
	if (this->animations.size() == 1) animations[0]->render(target, this->hitbox.getPosition());
}
