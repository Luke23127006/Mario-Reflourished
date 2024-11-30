#include "TileFactory.h"

Tile* TileFactory::createTile(sf::Vector2f position, TileType type)
{   
	switch (type)
	{
	case TileType::GROUND_BLOCK:
		return new Tile(position, Resources::textures["GROUND_BLOCK"]);
	case TileType::BRICK:
		return new Tile(position, Resources::textures["BRICK"], true);
	case TileType::BLOCK:
		return new Tile(position, Resources::textures["BLOCK"]);
	case TileType::BARRIER:
		return new Barrier(position);
	case TileType::ENEMY_BARRIER:
		return new EnemyBarrier(position);
	default:
		return nullptr;
	}
}
#include <iostream>
Tile* TileFactory::createTile(sf::Vector2f position, std::string type)
{
	type = encodeString(type);
	if (type == "ground block") return new Tile(position, Resources::textures["GROUND_BLOCK"], false, false);
	if (type == "brick") return new Tile(position, Resources::textures["BRICK"], true, true);
	if (type == "block") return new Tile(position, Resources::textures["BLOCK"], false, false);
	if (type == "barrier" || type == "BARRIER") return new Barrier(position);
	if (type == "enemy barrier") return new EnemyBarrier(position);
	if (type == "water surface") return new Water(position, true);
	if (type == "water below") return new Water(position, false);
	if (type == "lava surface") return new Lava(position, true);
	if (type == "lava below") return new Lava(position, false);
	if (type == "lucky block") return TileFactory::createLuckyBlock(position);
	if (type == "pipe top left") return new Pipe(position, PipeType::TOP_LEFT);
	if (type == "pipe top right") return new Pipe(position, PipeType::TOP_RIGHT);
	if (type == "pipe bottom left") return new Pipe(position, PipeType::BOTTOM_LEFT);
	if (type == "pipe bottom right") return new Pipe(position, PipeType::BOTTOM_RIGHT);
	return nullptr;
}

Tile* TileFactory::createPortal(sf::Vector2f position, sf::Vector2f destination)
{
    return new Portal(position, destination);
}

Tile* TileFactory::createPipe(sf::Vector2f position, PipeType type)
{
 	switch (type)
	{
	case PipeType::TOP_LEFT:
		return new Pipe(position, PipeType::TOP_LEFT);
	case PipeType::TOP_RIGHT:
		return new Pipe(position, PipeType::TOP_RIGHT);
	case PipeType::BOTTOM_LEFT:
		return new Pipe(position, PipeType::BOTTOM_LEFT);
	case PipeType::BOTTOM_RIGHT:
		return new Pipe(position, PipeType::BOTTOM_RIGHT);
	default:
		return nullptr;
	}
}

Tile* TileFactory::createLuckyBlock(sf::Vector2f position)
{
	int chance = rand() % 100;
	if (chance < 50)
	{
		return new LuckyBlock(position, LuckyBlockType::COIN);
	}
	else
	{
		return new LuckyBlock(position, LuckyBlockType::POWER_UP);
	}
}

Tile* TileFactory::createLava(sf::Vector2f position, std::string type)
{
	type = encodeString(type);
	if (type == "surface") return new Lava(position, true);
	return new Lava(position, false);
}

Tile* TileFactory::createWater(sf::Vector2f position, std::string type)
{
	type = encodeString(type);
	if (type == "surface") return new Water(position, true);
	return new Water(position, false);
}
