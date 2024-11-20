#pragma once

#include "Tile.h"
#include "Global.h"
#include "Resources.h"
#include "LuckyBlock.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Map
{
private:
	std::vector<std::vector<Tile*>> map;
	std::vector<LuckyBlock*> luckyBlocks;
	std::vector<std::vector<TileType>> mapData;
	sf::Vector2u size;
	sf::Vector2f position; // (top left corner)

public:
	Map(std::string fileName, sf::Vector2f position);
	virtual ~Map();

	sf::Vector2f getPosition();
	sf::Vector2u getSize();
	Tile& getTile(int i, int j);
	TileType getTileType(int i, int j);

	const bool insideMap(sf::FloatRect bounds) const;

	void update(float deltaTime);
	void render(sf::RenderTarget& target);
};

