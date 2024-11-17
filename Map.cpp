#include "Map.h"
#include <iostream>

Map::Map(std::string fileName, sf::Vector2f position) : 
	position(position)
{
	sf::Image image;
	image.loadFromFile(fileName);
	this->size = image.getSize();

	map.resize(this->size.x);
	mapData.resize(this->size.x);
	for (int i = 0; i < this->size.x; i++)
	{
		map[i].resize(this->size.y);
		mapData[i].resize(this->size.y);
	}

	for (int i = 0; i < this->size.x; i++)
		for (int j = 0; j < this->size.y; j++)
		{
			this->mapData[i][j] = TileType::EMPTY;
			sf::Color color = image.getPixel(i, j);
			if (color == sf::Color(0, 0, 0, 255))
			{
				this->mapData[i][j] = TileType::GROUND_BLOCK;
				this->map[i][j] = new Tile(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE), Resources::textures["GROUND_BLOCK"]);
			}
		}
}

Map::~Map()
{
	for (int i = 0; i < this->map.size(); i++)
		for (int j = 0; j < this->map[i].size(); j++)
			delete this->map[i][j];
}

sf::Vector2f Map::getPosition()
{
	return this->position;
}

sf::Vector2u Map::getSize()
{
	return this->size;
}

Tile& Map::getTile(int i, int j)
{
	return *this->map[i][j];
}

TileType Map::getTileType(int i, int j)
{
	return this->mapData[i][j];
}

const bool Map::insideMap(sf::FloatRect bounds) const
{
    sf::FloatRect mapBounds(this->position, sf::Vector2f(this->size.x * TILE_SIZE, this->size.y * TILE_SIZE));
	return mapBounds.intersects(bounds);
}

void Map::update(float deltaTime)
{
}

void Map::render(sf::RenderTarget& target)
{
	for (int i = 0; i < this->size.x; i++)
		for (int j = 0; j < this->size.y; j++)
		{
			if (this->mapData[i][j] == TileType::EMPTY) continue;
			this->map[i][j]->render(target);
		}
}
