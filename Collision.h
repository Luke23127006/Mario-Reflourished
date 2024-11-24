#pragma once

#include "Entity.h"
#include "Player.h"
#include "Tile.h"
#include "Coin.h"
#include "Map.h"
#include "Bullet.h"
#include "Portal.h"
#include "LuckyBlock.h"
#include "Enemy.h"
#include "Goomba.h"
#include "Shell.h"

class Collision
{
private:
	static bool checkAbove(sf::FloatRect firstBounds, sf::Vector2f firstLastPosition, sf::FloatRect secondBounds);
	static bool checkBelow(sf::FloatRect firstBounds, sf::Vector2f firstLastPosition, sf::FloatRect secondBounds);
public:
	static void handle_entity_map(Entity* entity, Map* map);
	static void handle_entity_tile(Entity* entity, Tile* tile);
	static void handle_player_enemy(Player* player, Enemy* enemy);
	static void handle_entity_shell(Entity* entity, Shell* shell);
	static void handle_player_coin(Player* player, Coin* coin);
	static void handle_bullet_tile(Bullet* bullet, Tile* tile);
};