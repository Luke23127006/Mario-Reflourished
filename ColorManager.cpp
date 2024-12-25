#include "ColorManager.h"

std::map<int, std::string> ColorManager::getObject;

void ColorManager::initColors()
{
    getObject[sf::Color(105, 27, 34, 255).toInteger()] = "ground_block";
    getObject[sf::Color(212, 102, 47, 255).toInteger()] = "brick";
    getObject[sf::Color(255, 151, 87, 255).toInteger()] = "lucky_block";
    getObject[sf::Color(34, 177, 76, 255).toInteger()] = "pipe";
    getObject[sf::Color(156, 52, 26, 255).toInteger()] = "block";
    getObject[sf::Color(53, 247, 106).toInteger()] = "pipe_destination";
    getObject[sf::Color(0, 0, 0, 255).toInteger()] = "barrier";
    getObject[sf::Color(255, 255, 255, 255).toInteger()] = "enemy barrier";

	getObject[sf::Color(237, 28, 36, 255).toInteger()] = "lava below";
	getObject[sf::Color(200, 28, 36, 255).toInteger()] = "lava surface";
    getObject[sf::Color(3, 169, 244, 255).toInteger()] = "water below";
    getObject[sf::Color(100, 169, 244, 255).toInteger()] = "water surface";

    getObject[sf::Color(255, 128, 0, 255).toInteger()] = "goomba";
    getObject[sf::Color(64, 128, 64, 255).toInteger()] = "koopa";
    getObject[sf::Color(200, 250, 100, 255).toInteger()] = "bird";
    getObject[sf::Color(145, 23, 228, 255).toInteger()] = "bowser";
    getObject[sf::Color(255, 100, 200, 255).toInteger()] = "wukong";
    getObject[sf::Color(255, 235, 59, 255).toInteger()] = "coin";
    getObject[sf::Color(205, 192, 110, 255).toInteger()] = "coin under water";

    getObject[sf::Color(255, 0, 0, 255).toInteger()] = "player";
}

ColorManager::ColorManager()
{
}

ColorManager::~ColorManager()
{
}
