#pragma once

#include "Tile.h"
#include "Resources.h"
#include "LuckyBlock.h"
#include "Pipe.h"
#include "Portal.h"
#include "Barrier.h"
#include "EnemyBarrier.h"

class TileFactory
{
public:
	static Tile* createTile(sf::Vector2f position, TileType type);
	static Tile* createPortal(sf::Vector2f position, sf::Vector2f destination);
	static Tile* createPipe(sf::Vector2f position, PipeType type);
	static Tile* createLuckyBlock(sf::Vector2f position, PowerUpType type);
};