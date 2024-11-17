#include "Collision.h"

void Collision::handle_entity_map(Entity* entity, Map* map)
{
	if (!map->insideMap(entity->getGlobalBounds())) return;

	sf::Vector2f size = map->getSize();
	int iRange = (int)(entity->getGlobalBounds().left / TILE_SIZE);
	int jRange = (int)(entity->getGlobalBounds().top / TILE_SIZE);

	sf::Vector2f delta(1, 1);
	sf::Vector2f ij(iRange - 1, jRange - 1);
	if (entity->getVelocity().x < 0.f) delta.x = -1, ij.x += 2;
	if (entity->getVelocity().y < 0.f) delta.y = -1, ij.y += 2;

	for (int i = ij.x; i != ij.x + 2 * delta.x; i += delta.x)
		for (int j = ij.y; j != ij.y + 2 * delta.y; j += delta.y)
		{
			if (i < 0 || i >= size.x || j < 0 || j >= size.y || map->getTileType(i, j) == TileType::EMPTY) continue;
			handle_entity_tile(entity, &map->getTile(i, j));
		}
}

void Collision::handle_entity_tile(Entity* entity, Tile* tile)
{
}

void Collision::handle_player_coin(Player* player, Coin* coin)
{
}