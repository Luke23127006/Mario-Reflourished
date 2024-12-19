#pragma once

#include "ColorManager.h"
#include "Entity.h"
#include "Global.h"
#include "PowerUp.h"
#include "Resources.h"
#include "TileFactory.h"
#include "EntityFactory.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Map
{
private:
	std::vector<std::vector<Tile*>> map;
	std::set<Tile*> needUpdatings;
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

	void addNeedUpdated(Tile* tile);

	const bool insideMap(sf::FloatRect bounds) const;
	const bool insideMap(Entity* entity) const;

	void update(float deltaTime, std::vector<Entity*>& entities);
	void render(sf::RenderWindow& target);
	void render(sf::RenderTarget& target, sf::Vector2f center);
};

