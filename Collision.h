#pragma once

#include "Entity.h"
#include "Player.h"
#include "Tile.h"
#include "Coin.h"
#include "Map.h"
#include "Bullet.h"
#include "LuckyBlock.h"

class Collision
{
public:
	static void handle_entity_map(Entity* entity, Map* map);
	static void handle_entity_tile(Entity* entity, Tile* tile);
	static void handle_player_coin(Player* player, Coin* coin);
	static void handle_bullet_tile(Bullet* bullet, Tile* tile);
};