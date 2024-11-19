#include "Resources.h"
#include <iostream>

std::map<std::string, sf::Texture> Resources::textures;
std::map<std::string, sf::Font> Resources::fonts;
std::map<std::string, sf::SoundBuffer> Resources::sounds;

void Resources::initTextures()
{
    // mario
    textures["MARIO_IDLE"].loadFromFile("./Resources/Characters/Mario/mario_idle.png");
	textures["MARIO_WALK"].loadFromFile("./Resources/Characters/Mario/mario_walk.png");
	textures["MARIO_JUMP"].loadFromFile("./Resources/Characters/Mario/mario_jump.png");
	textures["MARIO_DIE"].loadFromFile("./Resources/Characters/Mario/mario_die.png");
    textures["Welcome Background"].loadFromFile("./Resources/Background/MarioWelcomeIT.png");
    textures["Login Background"] = textures["Welcome Background"];
    textures["Play Background"].loadFromFile("./Resources/Background/Robot.jpg");
    textures["Select Level Background"].loadFromFile("./Resources/Background/EndTime.jpg");
}

void Resources::initFonts()
{
    fonts["Standard"].loadFromFile("./Resources/Fonts/Mario.ttf");
}

void Resources::initSounds()
{
}

Resources::Resources()
{
    this->initTextures();
    this->initFonts();
    this->initSounds();
}

Resources::~Resources()
{
}