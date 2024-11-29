#include "Resources.h"
#include <iostream>

std::map<std::string, sf::Texture> Resources::textures;
std::map<std::string, sf::Font> Resources::fonts;
std::map<std::string, sf::SoundBuffer> Resources::sounds;

void Resources::initResources()
{
    initTextures();
    initFonts();
    //initSounds();
}

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
	textures["EMPTY_BLOCK"].loadFromFile(TILES_DIRECTORY + "Empty Block.png");
	textures["PIPE_TOP_LEFT"].loadFromFile(TILES_DIRECTORY + "Pipe Top Left.png");
	textures["PIPE_TOP_RIGHT"].loadFromFile(TILES_DIRECTORY + "Pipe Top Right.png");
	textures["PIPE_BOTTOM_LEFT"].loadFromFile(TILES_DIRECTORY + "Pipe Bottom Left.png");
	textures["PIPE_BOTTOM_RIGHT"].loadFromFile(TILES_DIRECTORY + "Pipe Bottom Right.png");
	textures["SPIKE"].loadFromFile(TILES_DIRECTORY + "Spike.png");
	textures["LAVA_SURFACE"].loadFromFile(TILES_DIRECTORY + "Lava Surface.png");
	textures["LAVA_BELOW"].loadFromFile(TILES_DIRECTORY + "Lava Below.png");
	textures["WATER_SURFACE"].loadFromFile(TILES_DIRECTORY + "Water Surface.png");
	textures["WATER_BELOW"].loadFromFile(TILES_DIRECTORY + "Water Below.png");


	//Goomba
	textures["GOOMBA"].loadFromFile(ENEMIES_DIRECTORY + "goomba.png");
	
	//Koopa
	textures["KOOPA"].loadFromFile(ENEMIES_DIRECTORY + "Green.png");
	
	//Koopa Shell
	textures["KOOPA_SHELL"].loadFromFile(ENEMIES_DIRECTORY + "GreenShell.png");

	//Plant
	textures["GREEN_PLANT"].loadFromFile(ENEMIES_DIRECTORY + "GreenPlant.png");
	textures["RED_PLANT"].loadFromFile(ENEMIES_DIRECTORY + "RedPlant.png");

	// Fireball
	textures["FIREBALL"].loadFromFile(ITEMS_DIRECTORY + "Fireball.png");

	// Boss
	textures["BOSS"].loadFromFile(ENEMIES_DIRECTORY + "Boss.png");

	// Banzai Bill
	textures["BANZAI_BILL"].loadFromFile(ENEMIES_DIRECTORY + "BanzaiBill.png");

	// coin
	textures["COIN"].loadFromFile(ITEMS_DIRECTORY + "Coin.png");

	// all above textures are smooth
	for (auto& t : textures) t.second.setSmooth(true);
	// all below textures are not smooth
	

    // UI
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
}

Resources::~Resources()
{
}