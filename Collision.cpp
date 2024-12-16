#include "Collision.h"
#include <iostream>
#include <algorithm>

void Collision::handle_entity_map(Entity* entity, Map* map)
{
	if (!map->insideMap(entity)) return;

	sf::Vector2u size = map->getSize();
	int i = (1.f * (entity->getGlobalBounds().left - map->getPosition().x) / TILE_SIZE);
	int j = (1.f * (entity->getGlobalBounds().top - map->getPosition().y) / TILE_SIZE);

	entity->setOnGround(false);
	entity->setUnderWater(false);
	std::vector<Tile*> tiles;
	for (int _i = i; _i < i + 3; _i++)
	{
		for (int _j = j; _j < j + 3; _j++)
		{
			if (0 <= _i && _i < size.x && 0 <= _j && _j < size.y && map->getTileType(_i, _j) != TileType::EMPTY)
			{
				tiles.push_back(&map->getTile(_i, _j));
			}
		}
	}

	if (tiles.empty()) return;

	std::sort(tiles.begin(), tiles.end(), [entity](Tile* a, Tile* b) {
		sf::Vector2f entityCenter = sf::Vector2f(entity->getGlobalBounds().left + entity->getGlobalBounds().width / 2,
			entity->getGlobalBounds().top + entity->getGlobalBounds().height / 2);
		sf::Vector2f aCenter = sf::Vector2f(a->getGlobalBounds().left + a->getGlobalBounds().width / 2,
			a->getGlobalBounds().top + a->getGlobalBounds().height / 2);
		sf::Vector2f bCenter = sf::Vector2f(b->getGlobalBounds().left + b->getGlobalBounds().width / 2,
			b->getGlobalBounds().top + b->getGlobalBounds().height / 2);

		float distanceA = sqrt(pow(entityCenter.x - aCenter.x, 2) + pow(entityCenter.y - aCenter.y, 2));
		float distanceB = sqrt(pow(entityCenter.x - bCenter.x, 2) + pow(entityCenter.y - bCenter.y, 2));

		return distanceA < distanceB;
		});

	for (auto& t : tiles)
	{
		handle_entity_tile(entity, t);
		if (t->isNeedUpdating()) map->addNeedUpdated(t);
	}
}

void Collision::handle_entity_tile(Entity* entity, Tile* tile)
{
	entity->collisionTile(tile);
	return;

	// enemies is blocked by enemy barrier
	if (!isDerivedFrom<Enemy>(*entity) && isType<EnemyBarrier>(*tile)) return;

	// powerup is RISING from the Lucky Block
	if (isType<PowerUp>(*entity) && entity->getVelocity().x == 0) return;

	// underwater
	if (isType<Water>(*tile))
	{
		//Collision::handle_entity_water(entity, dynamic_cast<Water*>(tile));
		return;
	}

	sf::FloatRect entityBounds = entity->getGlobalBounds();
	sf::Vector2f lastPosition = entity->getLastPosition();
	sf::FloatRect tileBounds = tile->getGlobalBounds();

	bool above = checkAbove(entityBounds, lastPosition, tileBounds);
	bool below = checkBelow(entityBounds, lastPosition, tileBounds);

	// Entity in ON GROUND
	if (checkOnGround(entityBounds, tileBounds) && tile->isSolid())
	{
		entity->setOnGround(true);
		if (tile->isHarming())
		{
			if (isDerivedFrom<Enemy>(*entity))
			{
				dynamic_cast<Enemy*>(entity)->die();
			}
			else
			{
				entity->jump();
			}
		}
	}
	// Entity in INTERSECT with TILE
	if (entityBounds.intersects(tileBounds))
	{
		if (tile->isDanger())
		{
			entity->die();
		}
		else if (isType<Portal>(*tile) && entityBounds.left > tileBounds.left)
		{
			entity->setPosition(dynamic_cast<Portal*>(tile)->getDestination());
		}
		else if (!tile->isSolid())
		{
			return;
		}
		else if (above)
		{
			entity->setOnGround(true);
			entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0.f));
			entity->setPosition(sf::Vector2f(entity->getPosition().x, tileBounds.top - entityBounds.height));

			// BULLET bounces when touching the ground
			if (isType<Bullet>(*entity))
			{
				dynamic_cast<Bullet*>(entity)->bounce();
			}
		}
		else if (below)
		{
			if (isType<Player>(*entity))
			{
				dynamic_cast<Player*>(entity)->stopJumping();
			}

			entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0.f));
			entity->setPosition(sf::Vector2f(entity->getPosition().x, tileBounds.top + tileBounds.height));

			// PLAYER collision with TILE from below
			if (isType<Player>(*entity) && !entity->isUnderWater())
			{
				Player* player = dynamic_cast<Player*>(entity);
				if (player->hasPowerUp(PowerUpType::MUSHROOM))
				{
					if (tile->isBreakable()) tile->seftBreak();
				}
				tile->shake();
			}
		}
		else
		{
			// BULLET expire when touching the wall
			if (isType<Bullet>(*entity))
			{
				dynamic_cast<Bullet*>(entity)->die();
			}

			// PLAYER
			if (entityBounds.left <= tileBounds.left)
			{
				if (isType<Player>(*entity)) entity->setVelocity(sf::Vector2f(0.f, entity->getVelocity().y));
				entity->setPosition(sf::Vector2f(tileBounds.left - entityBounds.width, entity->getPosition().y));
			}
			else if (entityBounds.left > tileBounds.left)
			{
				if (isType<Player>(*entity)) entity->setVelocity(sf::Vector2f(0.f, entity->getVelocity().y));
				entity->setPosition(sf::Vector2f(tileBounds.left + tileBounds.width, entity->getPosition().y));
			}

			// ENEMY
			if (isDerivedFrom<Enemy>(*entity))
			{
				dynamic_cast<Enemy*>(entity)->setCollide(true);
			}

			// SHELL
			if (isType<Shell>(*entity))
			{
				dynamic_cast<Shell*>(entity)->turnAround();
			}

			// POWERUP (MUSHROOM)
			if (isType<PowerUp>(*entity))
			{
				dynamic_cast<PowerUp*>(entity)->turnAround();
			}
		}
	}
}

void Collision::handle_entity_entity(Entity* entity, Entity* other)
{
	Direction from = Direction::NONE;
	entity->collisionEntity(other, from);
	if (from == Direction::NONE) return;
	if (isDerivedFrom<Player>(*other))
	{
		entity->collisionEntity(dynamic_cast<Player*>(other), from);
	}
	else if (isDerivedFrom<Enemy>(*other))
	{
		entity->collisionEntity(dynamic_cast<Enemy*>(other), from);
	}
	else if (isDerivedFrom<Bullet>(*other))
	{
		entity->collisionEntity(dynamic_cast<Bullet*>(other), from);
	}
	else if (isDerivedFrom<Shell>(*other))
	{
		entity->collisionEntity(dynamic_cast<Shell*>(other), from);
	}
	else if (isDerivedFrom<PowerUp>(*other))
	{
		entity->collisionEntity(dynamic_cast<PowerUp*>(other), from);
	}
}

void Collision::handle_entity_spikeWall(Entity* entity, SpikeWall* spikeWall)
{
	if (entity->getGlobalBounds().left < spikeWall->getGLobalBounds().left + spikeWall->getGlobalBounds().width)
	{
		entity->die();
	}
}

void Collision::handle_player_coin(Player* player, Coin* coin)
{
	if (player->getGlobalBounds().intersects(coin->getGlobalBounds()))
	{
		player->addCoin();
		coin->setEnabled(false);
	}
}