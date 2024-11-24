#pragma once

#include "Global.h"

#include <SFML/Graphics.hpp>
#include <map>

class ColorManager
{
public:
	static std::map<int, TileType> getTileAsColor;
	static std::map<int, EnemyType> getEnemyAsColor;

	static void initColors();

	ColorManager();
	virtual ~ColorManager();
};

