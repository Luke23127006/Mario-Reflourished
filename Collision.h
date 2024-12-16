#pragma once

#include "EntityFactory.h"
#include "TileFactory.h"
#include "Coin.h"
#include "Map.h"
#include "SpikeWall.h"

class Collision
{
private:
public:
	static void handle_entity_map(Entity* entity, Map* map);
	static void handle_entity_tile(Entity* entity, Tile* tile);
	static void handle_entity_entity(Entity* entity, Entity* other);
	static void handle_entity_spikeWall(Entity* entity, SpikeWall* spikeWall);
	static void handle_player_coin(Player* player, Coin* coin);
};