#include "Collision.h"
#include <iostream>
#include <algorithm>

bool Collision::checkAbove(sf::FloatRect firstBounds, sf::Vector2f firstLastPosition, sf::FloatRect secondBounds)
{
	if ((firstLastPosition.x + firstBounds.width > secondBounds.left && firstLastPosition.x - secondBounds.left <= secondBounds.width) ||
		(firstLastPosition.x + firstBounds.width < secondBounds.left && secondBounds.left - firstLastPosition.x <= firstBounds.width))
	{
		return (firstLastPosition.y + firstBounds.height <= secondBounds.top);
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

void Collision::handle_entity_map(Entity* entity, Map* map)
{
	if (!map->insideMap(entity->getGlobalBounds())) return;

	sf::Vector2u size = map->getSize();
	float i = (1.f * entity->getGlobalBounds().left / TILE_SIZE);
	float j = (1.f * entity->getGlobalBounds().top / TILE_SIZE);

	entity->setOnGround(false);
	std::vector<Tile*> tiles;
	if (0 <= ceil(i) && ceil(i) < size.x && 0 <= ceil(j) && ceil(j) < size.y && map->getTileType(ceil(i), ceil(j)) != TileType::EMPTY)
		tiles.push_back(&map->getTile(ceil(i), ceil(j)));
	if (0 <= ceil(i) && ceil(i) < size.x && 0 <= floor(j) && floor(j) < size.y && map->getTileType(ceil(i), floor(j)) != TileType::EMPTY)
		tiles.push_back(&map->getTile(ceil(i), floor(j)));
	if (0 <= floor(i) && floor(i) < size.x && 0 <= ceil(j) && ceil(j) < size.y && map->getTileType(floor(i), ceil(j)) != TileType::EMPTY)
		tiles.push_back(&map->getTile(floor(i), ceil(j)));
	if (0 <= floor(i) && floor(i) < size.x && 0 <= floor(j) && floor(j) < size.y && map->getTileType(floor(i), floor(j)) != TileType::EMPTY)
		tiles.push_back(&map->getTile(floor(i), floor(j)));

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
		handle_entity_tile(entity, t);
}

void Collision::handle_entity_tile(Entity* entity, Tile* tile)
{
	if (isType<Player>(*entity) && isType<EnemyBarrier>(*tile)) return;

	sf::FloatRect entityBounds = entity->getGlobalBounds();
	sf::Vector2f lastPosition = entity->getLastPosition();
	sf::FloatRect tileBounds = tile->getGlobalBounds();

	bool above = checkAbove(entityBounds, lastPosition, tileBounds);
	bool below = checkBelow(entityBounds, lastPosition, tileBounds);

	if ((lastPosition.x + entityBounds.width > tileBounds.left && lastPosition.x - tileBounds.left <= tileBounds.width) ||
		(lastPosition.x + entityBounds.width < tileBounds.left && tileBounds.left - lastPosition.x <= entityBounds.width))
	{
		if (lastPosition.y + entityBounds.height <= tileBounds.top) above = true;
		else if (ceil(lastPosition.y) >= tileBounds.top + tileBounds.height) below = true;
	}

	if (entityBounds.left <= tileBounds.left && entityBounds.left + entityBounds.width >= tileBounds.left ||
		entityBounds.left >= tileBounds.left && entityBounds.left <= tileBounds.left + tileBounds.width)
	{
		if (entityBounds.top + entityBounds.height == tileBounds.top)
			entity->setOnGround(true);
	}

	if (entityBounds.intersects(tileBounds))
	{
		if (isType<Portal>(*tile) && entityBounds.left > tileBounds.left)
		{
			entity->setPosition(dynamic_cast<Portal*>(tile)->getDestination());
		}
		else if (above)
		{
			entity->setOnGround(true);
			entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0.f));
			entity->setPosition(sf::Vector2f(entity->getPosition().x, tileBounds.top - entityBounds.height));
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
		}
		else
		{
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
		}
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

void Collision::handle_player_coin(Player* player, Coin* coin)
{
}

void Collision::handle_bullet_tile(Bullet* bullet, Tile* tile)
{
}
