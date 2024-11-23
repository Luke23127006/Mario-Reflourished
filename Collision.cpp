#include "Collision.h"
#include <iostream>
#include <algorithm>

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
	if (typeid(*entity) == typeid(Player) && typeid(*tile) == typeid(EnemyBarrier)) return;
	
	sf::FloatRect entityBounds = entity->getGlobalBounds();
	sf::Vector2f lastPosition = entity->getLastPosition();
	sf::FloatRect tileBounds = tile->getGlobalBounds();

	bool above = false;
	bool below = false;

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
		if (typeid(*tile) == typeid(Portal) && entityBounds.left > tileBounds.left)
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
			if (typeid(*entity) == typeid(Player))
			{
				dynamic_cast<Player*>(entity)->stopJumping();
			}

			entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0.f));
			entity->setPosition(sf::Vector2f(entity->getPosition().x, tileBounds.top + tileBounds.height));

			if (typeid(*tile) == typeid(LuckyBlock))
			{
				dynamic_cast<LuckyBlock*>(tile)->activate();
			}
		}
		else
		{
			if (entityBounds.left <= tileBounds.left)
			{
				if (typeid(*entity) == typeid(Player)) entity->setVelocity(sf::Vector2f(0.f, entity->getVelocity().y));
				entity->setPosition(sf::Vector2f(tileBounds.left - entityBounds.width, entity->getPosition().y));
			}
			else if (entityBounds.left > tileBounds.left)
			{
				if (typeid(*entity) == typeid(Player)) entity->setVelocity(sf::Vector2f(0.f, entity->getVelocity().y));
				entity->setPosition(sf::Vector2f(tileBounds.left + tileBounds.width, entity->getPosition().y));
			}

			Enemy* e = dynamic_cast<Enemy*>(entity);
			if (e != nullptr)
			{
				e->turnAround();
			}
		}
	}
}

void Collision::handle_player_enemy(Player* player, Enemy* enemy)
{
	sf::FloatRect playerBounds = player->getGlobalBounds();
	sf::Vector2f lastPosition = player->getLastPosition();
	sf::FloatRect enemyBounds = enemy->getGlobalBounds();

	bool above = false;

	if ((lastPosition.x + playerBounds.width > enemyBounds.left && lastPosition.x - enemyBounds.left <= enemyBounds.width) ||
		(lastPosition.x + playerBounds.width < enemyBounds.left && enemyBounds.left - lastPosition.x <= playerBounds.width))
	{
		if (lastPosition.y + playerBounds.height <= enemyBounds.top) above = true;
	}

	if (playerBounds.intersects(enemyBounds))
	{
		if (above)
		{
			player->setVelocity(sf::Vector2f(player->getVelocity().x, -PLAYER_JUMP_STRENGHT / 2));
			enemy->die(EnemyDieType::SQUISH);
		}
		else
		{
			player->die();
		}
	}
}

void Collision::handle_player_coin(Player* player, Coin* coin)
{
}

void Collision::handle_bullet_tile(Bullet* bullet, Tile* tile)
{
}
