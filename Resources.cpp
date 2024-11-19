#include "Resources.h"
#include <iostream>

std::map<std::string, sf::Texture> Resources::textures;
std::map<std::string, sf::Font> Resources::fonts;
std::map<std::string, sf::SoundBuffer> Resources::sounds;
sf::Color* Resources::getColor;

void Resources::initTextures()
{
    // mario
    textures["MARIO_IDLE"].loadFromFile(CHARACTERS_DIRECTORY + "mario_idle.png");
	textures["MARIO_WALK"].loadFromFile(CHARACTERS_DIRECTORY + "mario_walk.png");
	textures["MARIO_JUMP"].loadFromFile(CHARACTERS_DIRECTORY + "mario_jump.png");
	textures["MARIO_DIE"].loadFromFile(CHARACTERS_DIRECTORY + "mario_die.png");

    // tiles
	textures["GROUND_BLOCK"].loadFromFile(TILES_DIRECTORY + "Ground Block.png");
	textures["BRICK"].loadFromFile(TILES_DIRECTORY + "Bricks.png");
	textures["LUCKY_BLOCK"].loadFromFile(TILES_DIRECTORY + "Lucky Block.png");
	textures["PIPE"].loadFromFile(TILES_DIRECTORY + "Pipe.png");
	textures["BLOCK"].loadFromFile(TILES_DIRECTORY + "Block.png");

    // UI
    textures["Welcome Background"].loadFromFile("./Resources/Background/MarioWelcomeIT.png");
    textures["Play Background"].loadFromFile("./Resources/Background/Robot.jpg");
    textures["Select Level Background"].loadFromFile("./Resources/Background/EndTime.jpg");

	

	for (auto& t : textures)
	{
		t.second.setSmooth(true);
	}
}

void Resources::initFonts()
{
    fonts["Standard"].loadFromFile("./Resources/Fonts/Mario.ttf");
}

void Resources::initSounds()
{
}

void Resources::initColors()
{
	getColor = new sf::Color[INT(TileType::NUM_TILE_TYPES)];
	getColor[INT(TileType::EMPTY)] = sf::Color::White;
	getColor[INT(TileType::GROUND_BLOCK)] = sf::Color(105, 27, 34, 255);
	getColor[INT(TileType::BRICK)] = sf::Color(212, 102, 47, 255);
	getColor[INT(TileType::LUCKY_BLOCK)] = sf::Color(255, 151, 87, 255);
	getColor[INT(TileType::PIPE)] = sf::Color(34, 177, 76, 255);
	getColor[INT(TileType::BLOCK)] = sf::Color(156, 52, 26, 255);
}

Resources::Resources()
{
    this->initTextures();
    this->initFonts();
    this->initSounds();
	this->initColors();
}

Resources::~Resources()
{
	delete getColor;
}