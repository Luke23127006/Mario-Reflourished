#include "Collision.h"
#include <iostream>

void Collision::handle_entity_map(Entity* entity, Map* map)
{
	if (!map->insideMap(entity->getGlobalBounds())) return;

	sf::Vector2u size = map->getSize();
	int iRange = (int)(entity->getGlobalBounds().left / TILE_SIZE);
	int jRange = (int)(entity->getGlobalBounds().top / TILE_SIZE);

	entity->setOnGround(false);
	if (entity->getVelocity().y >= 0)
	{
		for (int i = std::max(0, iRange - 1); i < std::min(int(size.x), iRange + 2); i++)
			for (int j = std::max(0, jRange - 1); j < std::min(int(size.y), jRange + 2); j++)
			{
				if (map->getTileType(i, j) == TileType::EMPTY) continue;
				handle_entity_tile(entity, &map->getTile(i, j));
			}
	}
	else
	{
		for (int i = std::max(0, iRange - 1); i < std::min(int(size.x), iRange + 2); i++)
			for (int j = std::min(int(size.y), jRange + 2); j >= std::max(0, jRange - 1); j--)
			{
				if (map->getTileType(i, j) == TileType::EMPTY) continue;
				handle_entity_tile(entity, &map->getTile(i, j));
			}
	}
}

void Collision::handle_entity_tile(Entity* entity, Tile* tile)
{
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
		if (above)
		{
			entity->setOnGround(true);
			entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0.f));
			entity->setPosition(sf::Vector2f(entity->getPosition().x, tileBounds.top - entityBounds.height));
		}
		else if (below)
		{
			entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0.f));
			entity->setPosition(sf::Vector2f(entity->getPosition().x, tileBounds.top + tileBounds.height));
		}
		else
		{
			if (entityBounds.left <= tileBounds.left)
			{
				entity->setVelocity(sf::Vector2f(0.f, entity->getVelocity().y));
				entity->setPosition(sf::Vector2f(tileBounds.left - entityBounds.width, entity->getPosition().y));
			}
			else if (entityBounds.left > tileBounds.left)
			{
				entity->setVelocity(sf::Vector2f(0.f, entity->getVelocity().y));
				entity->setPosition(sf::Vector2f(tileBounds.left + tileBounds.width, entity->getPosition().y));
			}
		}
	}
}

void Collision::handle_player_coin(Player* player, Coin* coin)
{
}