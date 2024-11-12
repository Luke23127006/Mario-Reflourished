#pragma once

#include "Tile.h"
#include "Global.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Map
{
private:
	std::vector<std::vector<Tile*>> map;
	std::vector<std::vector<TileType>> mapData;
	sf::Vector2f size;
	sf::Vector2f position; // (top left corner)

public:
	Map(std::string fileName, sf::Vector2i size, sf::Vector2f position);
	virtual ~Map();

	void getPosition();
	void getSize();

	void update(float deltaTime);
	void render(sf::RenderTarget& target);
};

