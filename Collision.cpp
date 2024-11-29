#include "Collision.h"
#include <iostream>
#include <algorithm>

bool Collision::checkAbove(sf::FloatRect firstBounds, sf::Vector2f firstLastPosition, sf::FloatRect secondBounds)
{
	if ((firstLastPosition.x + firstBounds.width > secondBounds.left && firstLastPosition.x - secondBounds.left <= secondBounds.width) ||
		(firstLastPosition.x + firstBounds.width < secondBounds.left && secondBounds.left - firstLastPosition.x <= firstBounds.width))
	{
		return (floor(firstLastPosition.y + firstBounds.height) <= secondBounds.top);
	}
	return false;
}

bool Collision::checkBelow(sf::FloatRect firstBounds, sf::Vector2f firstLastPosition, sf::FloatRect secondBounds)
{
	if ((firstLastPosition.x + firstBounds.width > secondBounds.left && firstLastPosition.x - secondBounds.left <= secondBounds.width) ||
		(firstLastPosition.x + firstBounds.width < secondBounds.left && secondBounds.left - firstLastPosition.x <= firstBounds.width))
	{
		return (ceil(firstLastPosition.y) >= secondBounds.top + secondBounds.height);
	}
	return false;
}

bool Collision::checkOnGround(sf::FloatRect firstBounds, sf::FloatRect secondBounds)
{
	if (firstBounds.left <= secondBounds.left && firstBounds.left + firstBounds.width >= secondBounds.left ||
		firstBounds.left >= secondBounds.left && firstBounds.left <= secondBounds.left + secondBounds.width)
	{
		return (firstBounds.top + firstBounds.height == secondBounds.top);
	}
	return false;
}

void Collision::handle_entity_map(Entity* entity, Map* map)
{
	if (!map->insideMap(entity->getGlobalBounds())) return;

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
	if (!isDerivedFrom<Enemy>(*entity) && isType<EnemyBarrier>(*tile)) return;
	if (isType<PowerUp>(*entity) && entity->getVelocity().x == 0) return;
	if (isType<Water>(*tile))
	{
		Collision::handle_entity_water(entity, dynamic_cast<Water*>(tile));
		return;
	}
	if (!tile->isSolid()) return;

	sf::FloatRect entityBounds = entity->getGlobalBounds();
	sf::Vector2f lastPosition = entity->getLastPosition();
	sf::FloatRect tileBounds = tile->getGlobalBounds();

	bool above = checkAbove(entityBounds, lastPosition, tileBounds);
	bool below = checkBelow(entityBounds, lastPosition, tileBounds);

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
		else if (above)
		{
			entity->setOnGround(true);
			entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0.f));
			entity->setPosition(sf::Vector2f(entity->getPosition().x, tileBounds.top - entityBounds.height));

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

			if (isType<LuckyBlock>(*tile))
			{
				dynamic_cast<LuckyBlock*>(tile)->activate();
			}

			if (isType<Player>(*entity) && !entity->isUnderWater())
			{
				Player* player = dynamic_cast<Player*>(entity);
				if (player->hasPowerUp(PowerUpType::MUSHROOM))
					tile->seftBreak();
				else 
					tile->shake();
			}
		}
		else
		{
			if (isType<Bullet>(*entity))
			{
				dynamic_cast<Bullet*>(entity)->die();
			}

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

			if (isDerivedFrom<Enemy>(*entity))
			{
				dynamic_cast<Enemy*>(entity)->turnAround();
			}
			if (isType<Shell>(*entity))
			{
				dynamic_cast<Shell*>(entity)->turnAround();
			}
			if (isType<PowerUp>(*entity))
			{
				dynamic_cast<PowerUp*>(entity)->turnAround();
			}
		}
	}
}

void Collision::handle_entity_water(Entity* entity, Water* water)
{
	if (entity->getGlobalBounds().intersects(water->getGlobalBounds()))
	{
		entity->setUnderWater(true);
	}
}

void Collision::handle_player_enemy(Player* player, Enemy* enemy)
{
	sf::FloatRect playerBounds = player->getGlobalBounds();
	sf::Vector2f lastPosition = player->getLastPosition();
	sf::FloatRect enemyBounds = enemy->getGlobalBounds();

	bool above = checkAbove(playerBounds, lastPosition, enemyBounds);

	if (playerBounds.intersects(enemyBounds))
	{
		if (above)
		{
			player->setVelocity(sf::Vector2f(player->getVelocity().x, -PLAYER_JUMP_STRENGHT / 2));
			enemy->squished();
		}
		else
		{
			player->die();
		}
	}
}

void Collision::handle_entity_shell(Entity* entity, Shell* shell)
{
	sf::FloatRect entityBounds = entity->getGlobalBounds();
	sf::Vector2f lastPosition = entity->getLastPosition();
	sf::FloatRect shellBounds = shell->getGlobalBounds();

	bool above = checkAbove(entityBounds, lastPosition, shellBounds);

	if (entityBounds.intersects(shellBounds))
	{
		if (above)
		{
			entity->setPosition(sf::Vector2f(entity->getPosition().x, shellBounds.top - entityBounds.height));
			entity->setVelocity(sf::Vector2f(entity->getVelocity().x, -PLAYER_JUMP_STRENGHT / 2));
			shell->switchActivation();
		}
		else if (!shell->isActivated())
		{
			if (entity->getVelocity().x > 0)
			{
				shell->switchActivation();
				entity->setPosition(sf::Vector2f(shellBounds.left - entityBounds.width, entity->getPosition().y));
				shell->setVelocity(sf::Vector2f(KOOPA_SHELL_SPEED, 0.f));
			}
			else if (entity->getVelocity().x < 0)
			{
				shell->switchActivation();
				entity->setPosition(sf::Vector2f(shellBounds.left + shellBounds.width, entity->getPosition().y));
				shell->setVelocity(sf::Vector2f(-KOOPA_SHELL_SPEED, 0.f));
			}
		}
		else
		{
			entity->die();
		}
	}
}

void Collision::handle_bullet_enemy(Bullet* bullet, Enemy* enemy)
{
	sf::FloatRect bulletBounds = bullet->getGlobalBounds();
	sf::FloatRect enemyBounds = enemy->getGlobalBounds();
	if (bulletBounds.intersects(enemyBounds))
	{
		bullet->die();
		enemy->die();
	}
}

void Collision::handle_player_powerUp(Player* player, PowerUp* powerUp)
{
	if (player->getGlobalBounds().intersects(powerUp->getGlobalBounds()))
	{
		player->gainPowerUp(*powerUp);
		powerUp->die();
	}
}

void Collision::handle_entity_spikeWall(Entity* entity, SpikeWall* spikeWall)
{
	if (entity->getGlobalBounds().intersects(spikeWall->getGlobalBounds()))
	{
		entity->die();
	}
}

void Collision::handle_player_coin(Player* player, Coin* coin)
{
}