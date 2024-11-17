#include "Map.h"

Map::Map(std::string fileName, sf::Vector2i size, sf::Vector2f position)
{
	sf::Image image;
	image.loadFromFile(MAPS_DIRECTORY + fileName);
	for (int i = 0; i < size.x; i++)
		for (int j = 0; j < size.y; j++)
		{
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

sf::Vector2f Map::getSize()
{
	return this->size;
}

bool Map::insideMap(sf::Vector2f position)
{
	return position.x >= this->position.x && position.x <= this->position.x + TILE_SIZE * this->size.x &&
		position.y >= this->position.y && position.y <= this->position.y + TILE_SIZE * this->size.y;
}

void Map::update(float deltaTime)
{
}

void Map::render(sf::RenderTarget& target)
{
}
