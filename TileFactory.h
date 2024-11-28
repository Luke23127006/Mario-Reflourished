#pragma once

#include "Barrier.h"
#include "EnemyBarrier.h"
#include "LuckyBlock.h"
#include "Pipe.h"
#include "Portal.h"
#include "Resources.h"
#include "Tile.h"
#include "Lava.h"
#include "Water.h"

class TileFactory
{
public:
	static Tile* createTile(sf::Vector2f position, TileType type);
	static Tile* createPortal(sf::Vector2f position, sf::Vector2f destination);
	static Tile* createPipe(sf::Vector2f position, PipeType type);
	static Tile* createLuckyBlock(sf::Vector2f position);
	static Tile* createLava(sf::Vector2f position, bool isSurface);
	static Tile* createWater(sf::Vector2f position, bool isSurface);
};