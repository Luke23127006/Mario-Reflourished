#pragma once

#include "Tile.h"
#include "Global.h"
#include "Resources.h"
#include "LuckyBlock.h"
#include "Pipe.h"
#include "Portal.h"
#include "Barrier.h"
#include "UserInterface.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Map : public Scene
{
private:
	std::vector<std::vector<Tile*>> map;
	std::vector<LuckyBlock*> luckyBlocks;
	std::vector<std::vector<TileType>> mapData;
	sf::Vector2u size;
	sf::Vector2f position; // (top left corner)

	// UI
	bool goToSelectLevel = false;
	GameState levelState;

public:
	Map(std::string fileName, sf::Vector2f position, GameState levelState);
	virtual ~Map();

	sf::Vector2f getPosition();
	sf::Vector2u getSize();
	Tile& getTile(int i, int j);
	TileType getTileType(int i, int j);

	const bool insideMap(sf::FloatRect bounds) const;

	void update(float deltaTime) override;
	void render(sf::RenderWindow& target, bool& held) override;
	GameState getNextScene() override;
};

