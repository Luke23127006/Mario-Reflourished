#include "ColorManager.h"

std::map<int, TileType> ColorManager::getTileAsColor;
std::map<int, EnemyType> ColorManager::getEnemyAsColor;

void ColorManager::initColors()
{
	getTileAsColor[sf::Color(105, 27, 34, 255).toInteger()] = TileType::GROUND_BLOCK;
    getTileAsColor[sf::Color(212, 102, 47, 255).toInteger()] = TileType::BRICK;
    getTileAsColor[sf::Color(255, 151, 87, 255).toInteger()] = TileType::LUCKY_BLOCK;
    getTileAsColor[sf::Color(34, 177, 76, 255).toInteger()] = TileType::PIPE;
    getTileAsColor[sf::Color(156, 52, 26, 255).toInteger()] = TileType::BLOCK;
    getTileAsColor[sf::Color(53, 247, 106).toInteger()] = TileType::PIPE_DESTINATION;
    getTileAsColor[sf::Color(0, 0, 0, 255).toInteger()] = TileType::BARRIER;
    getTileAsColor[sf::Color(255, 255, 255, 255).toInteger()] = TileType::ENEMY_BARRIER;

    getEnemyAsColor[sf::Color(255, 128, 0, 255).toInteger()] = EnemyType::GOOMBA;
}

ColorManager::ColorManager()
{
}

ColorManager::~ColorManager()
{
}
