#include "Map.h"
#include <iostream>

Map::Map(std::string fileName, sf::Vector2f position) :
    position(position)
{
    sf::Image image;
    if (!image.loadFromFile(fileName))
    {
        throw std::runtime_error("Failed to load map image: " + fileName);
    }
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
    {
        for (int i = 0; i < this->size.x; i++)
        {
            this->mapData[i][j] = TileType::EMPTY;
            sf::Color color = image.getPixel(i, j);
            int colorCode = color.toInteger();

            // Check if the color exists in ColorManager
            if (ColorManager::getObject.find(colorCode) != ColorManager::getObject.end())
            {
                std::string tileName = ColorManager::getObject[colorCode];

                // Map the tile name to the corresponding TileType
                if (tileName == "ground_block")
                    this->mapData[i][j] = TileType::GROUND_BLOCK;
                else if (tileName == "brick")
                    this->mapData[i][j] = TileType::BRICK;
                else if (tileName == "lucky_block")
                    this->mapData[i][j] = TileType::LUCKY_BLOCK;
                else if (tileName == "pipe")
                    this->mapData[i][j] = TileType::PIPE;
                else if (tileName == "block")
                    this->mapData[i][j] = TileType::BLOCK;
                else if (tileName == "pipe_destination")
                    this->mapData[i][j] = TileType::PIPE_DESTINATION;
                else if (tileName == "barrier")
                    this->mapData[i][j] = TileType::BARRIER;
                else if (tileName == "enemy barrier")
                    this->mapData[i][j] = TileType::ENEMY_BARRIER;
                else if (tileName == "lava")
                    this->mapData[i][j] = TileType::LAVA;
				else if (tileName == "water")
					this->mapData[i][j] = TileType::WATER;
            }

            // Process the tile based on its type
            switch (this->mapData[i][j])
            {
            case TileType::LUCKY_BLOCK:
                this->map[i][j] = TileFactory::createLuckyBlock(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE));
                this->needUpdatings.insert(this->map[i][j]);
                break;

            case TileType::LAVA:
				this->map[i][j] = TileFactory::createLava(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE), true);
				break;

			case TileType::WATER:
				this->map[i][j] = TileFactory::createWater(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE), true);
				break;

            case TileType::PIPE:
                if (this->mapData[i][j - 1] == TileType::PIPE)
                {
                    if (this->mapData[i - 1][j] == TileType::PIPE)
                        this->map[i][j] = TileFactory::createPipe(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE), PipeType::BOTTOM_RIGHT);
                    else if (destination.empty())
                        this->map[i][j] = TileFactory::createPipe(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE), PipeType::BOTTOM_LEFT);
                    else
                    {
                        this->map[i][j] = TileFactory::createPortal(position + sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE), destination.back());
                        destination.pop_back();
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

void Map::addNeedUpdated(Tile* tile)
{
	this->needUpdatings.insert(tile);
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

void Map::update(float deltaTime, std::vector<Entity*>& entities)
{
	for (auto it = this->needUpdatings.begin(); it != this->needUpdatings.end();)
	{
		auto* tile = *it;
		if (isType<LuckyBlock>(*tile) && dynamic_cast<LuckyBlock*>(tile)->isActivated())
		{
			if (dynamic_cast<LuckyBlock*>(tile)->getType() == LuckyBlockType::POWER_UP)
			{
				entities.push_back(dynamic_cast<LuckyBlock*>(tile)->launchPowerUp());
			}
		}
		tile->update(deltaTime);

		if (!tile->isNeedUpdating()) it = this->needUpdatings.erase(it);
		else ++it;
	}
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
