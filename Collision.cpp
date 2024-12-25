#include "Collision.h"
#include <iostream>
#include <algorithm>

void Collision::handle_entity_map(Entity* entity, Map* map)
{
	if (!map->insideMap(entity))
	{
		entity->die();
		return;
	}	

	sf::Vector2u size = map->getSize();
	int i = (1.f * (entity->getGlobalBounds().left - map->getPosition().x) / TILE_SIZE);
	int j = (1.f * (entity->getGlobalBounds().top - map->getPosition().y) / TILE_SIZE);

	int iRange = int(entity->getGlobalBounds().width / TILE_SIZE) + 1;
	int jRange = int(entity->getGlobalBounds().height / TILE_SIZE) + 1;

	std::vector<Tile*> tiles;
	for (int _i = i; _i <= i + iRange; _i++)
	{
		for (int _j = j; _j <= j + jRange; _j++)
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
	entity->collideWithTile(tile);
}

void Collision::handle_entity_entity(Entity* entity, Entity* other)
{
	Direction from = Direction::NONE;
	entity->collideWithEntity(other, from);
	if (from == Direction::NONE) return;
	if (isDerivedFrom<Player>(*other))
	{
		entity->collideWithEntity(dynamic_cast<Player*>(other), from);
	}
	else if (isDerivedFrom<Enemy>(*other))
	{
		entity->collideWithEntity(dynamic_cast<Enemy*>(other), from);
	}
	else if (isDerivedFrom<Bullet>(*other))
	{
		entity->collideWithEntity(dynamic_cast<Bullet*>(other), from);
	}
	else if (isDerivedFrom<Shell>(*other))
	{
		entity->collideWithEntity(dynamic_cast<Shell*>(other), from);
	}
	else if (isDerivedFrom<PowerUp>(*other))
	{
		entity->collideWithEntity(dynamic_cast<PowerUp*>(other), from);
	}
	else if (isDerivedFrom<FireBall>(*other))
	{
		entity->collideWithEntity(dynamic_cast<FireBall*>(other), from);
	}
	else if (isDerivedFrom<WukongMagicRod>(*other))
	{
		entity->collideWithEntity(dynamic_cast<WukongMagicRod*>(other), from);
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