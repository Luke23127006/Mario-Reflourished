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

	std::vector<sf::Vector2f> destination;

	for (int j = 0; j < this->size.y; j++)
		for (int i = 0; i < this->size.x; i++)
		{
			this->mapData[i][j] = TileType::EMPTY;
			sf::Color color = image.getPixel(i, j);
			int colorCode = color.toInteger();

			this->mapData[i][j] = ColorManager::getTileAsColor[colorCode];
			switch (ColorManager::getTileAsColor[colorCode])
			{
			case TileType::LUCKY_BLOCK:
				this->map[i][j] = TileFactory::createLuckyBlock(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE), LuckyBlockType::COIN);
				this->luckyBlocks.push_back(dynamic_cast<LuckyBlock*>(this->map[i][j]));
				break;
			case TileType::PIPE:
				if (this->mapData[i][j - 1] == TileType::PIPE)
				{
					if (this->mapData[i - 1][j] == TileType::PIPE)
						this->map[i][j] = TileFactory::createPipe(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE), PipeType::BOTTOM_RIGHT);
					else
					{
						if (destination.empty())
						{
							this->map[i][j] = TileFactory::createPipe(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE), PipeType::BOTTOM_LEFT);
						}
						else
						{
							this->map[i][j] = TileFactory::createPortal(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE), destination.back());
							destination.pop_back();
						}
					}
				}
				else
				{
					if (this->mapData[i - 1][j] == TileType::PIPE)
						this->map[i][j] = TileFactory::createPipe(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE), PipeType::TOP_RIGHT);
					else
						this->map[i][j] = TileFactory::createPipe(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE), PipeType::TOP_LEFT);
				}
				break;
			case TileType::PIPE_DESTINATION:
				if (this->mapData[i][j - 1] == TileType::PIPE_DESTINATION)
				{
					if (this->mapData[i - 1][j] == TileType::PIPE_DESTINATION)
						this->map[i][j] = TileFactory::createPipe(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE), PipeType::BOTTOM_RIGHT);
					else
					{
						this->map[i][j] = TileFactory::createPipe(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE), PipeType::BOTTOM_LEFT);
						destination.push_back(position + sf::Vector2f(i * TILE_SIZE + this->map[i][j]->getGlobalBounds().width, j * TILE_SIZE));
					}
				}
				else
				{
					if (this->mapData[i - 1][j] == TileType::PIPE_DESTINATION)
						this->map[i][j] = TileFactory::createPipe(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE), PipeType::TOP_RIGHT);
					else
						this->map[i][j] = TileFactory::createPipe(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE), PipeType::TOP_LEFT);
				}
				break;
			default:
				this->map[i][j] = TileFactory::createTile(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE), this->mapData[i][j]);
				break;
			}
		}
}

Map::~Map()
{
	for (int i = 0; i < this->size.x; i++)
		while (!this->map[i].empty())
		{
			delete this->map[i].back();
			this->map[i].pop_back();
		}
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
	for (auto& lb : this->luckyBlocks)
		lb->update(deltaTime);
}

void Map::render(sf::RenderWindow& target)
{
	for (int i = 0; i < this->size.x; i++)
		for (int j = 0; j < this->size.y; j++)
		{
			if (this->mapData[i][j] == TileType::EMPTY) continue;
			this->map[i][j]->render(target);
		}
}
