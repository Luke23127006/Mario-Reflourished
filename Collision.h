#pragma once

#include "EntityFactory.h"
#include "TileFactory.h"
#include "Coin.h"
#include "Map.h"
#include "SpikeWall.h"

class Collision
{
private:
	static bool checkAbove(sf::FloatRect firstBounds, sf::Vector2f firstLastPosition, sf::FloatRect secondBounds);
	static bool checkBelow(sf::FloatRect firstBounds, sf::Vector2f firstLastPosition, sf::FloatRect secondBounds);
	static bool checkOnGround(sf::FloatRect firstBounds, sf::FloatRect secondBounds);
public:
	static void handle_entity_map(Entity* entity, Map* map);
	static void handle_entity_tile(Entity* entity, Tile* tile);
	static void handle_entity_water(Entity* entity, Water* water);
	static void handle_player_enemy(Player* player, Enemy* enemy);
	static void handle_entity_shell(Entity* entity, Shell* shell);
	static void handle_bullet_enemy(Bullet* bullet, Enemy* enemy);
	static void handle_player_powerUp(Player* player, PowerUp* powerUp);
	static void handle_entity_spikeWall(Entity* entity, SpikeWall* spikeWall);
	static void handle_player_coin(Player* player, Coin* coin);
};