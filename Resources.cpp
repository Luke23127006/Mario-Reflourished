#include "Resources.h"
#include <iostream>

std::map<std::string, sf::Texture> Resources::textures;
std::map<std::string, sf::Font> Resources::fonts;
std::map<std::string, sf::SoundBuffer> Resources::soundBuffers;
std::map<std::string, sf::Sound> Resources::sounds;

void Resources::initResources()
{
    initTextures();
    initFonts();
    initSounds();
}

void Resources::initTextures()
{
    // mario
    textures["MARIO_IDLE"].loadFromFile(CHARACTERS_DIRECTORY + "mario_idle.png");
	textures["MARIO_WALK"].loadFromFile(CHARACTERS_DIRECTORY + "mario_walk.png");
	textures["MARIO_JUMP"].loadFromFile(CHARACTERS_DIRECTORY + "mario_jump.png");
	textures["MARIO_SWIM"].loadFromFile(CHARACTERS_DIRECTORY + "mario_swim.png");
	textures["MARIO_DIE"].loadFromFile(CHARACTERS_DIRECTORY + "mario_die.png");

    // tiles
	textures["GROUND_BLOCK"].loadFromFile(TILES_DIRECTORY + "Ground Block.png"); // "Ground Block.png"
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
	textures["SPIKE_WALL"].loadFromFile(TILES_DIRECTORY + "Spike Wall.png");
	textures["VICTORY"].loadFromFile(TILES_DIRECTORY + "VICTORY.png");

	//Goomba
	textures["GOOMBA"].loadFromFile(ENEMIES_DIRECTORY + "goomba.png");
	
	//Koopa
	textures["KOOPA"].loadFromFile(ENEMIES_DIRECTORY + "Koopa.png");
	
	//Koopa Shell
	textures["KOOPA_SHELL"].loadFromFile(ENEMIES_DIRECTORY + "Shell.png");



	// Bird
	textures["NORMAL_BIRD"].loadFromFile(ENEMIES_DIRECTORY + "Bird/Normal_Bird.png");
	textures["ANGRY_BIRD"].loadFromFile(ENEMIES_DIRECTORY + "Bird/Angry_Bird.png");

	//Plant
	textures["GREEN_PLANT"].loadFromFile(ENEMIES_DIRECTORY + "GreenPlant.png");
	textures["RED_PLANT"].loadFromFile(ENEMIES_DIRECTORY + "RedPlant.png");



	// Wukong
	
	textures["WUKONG"].loadFromFile(ENEMIES_DIRECTORY + "WukongSuper.png");
	textures["MAGIC_ROD"].loadFromFile(ENEMIES_DIRECTORY + "MagicRodSuper.png");
	//Item
	textures["COIN"].loadFromFile(ITEMS_DIRECTORY + "Coin.png");
	textures["POWER_UPS"].loadFromFile(ITEMS_DIRECTORY + "Power Ups.png");
	textures["BULLET"].loadFromFile(ITEMS_DIRECTORY + "Fire Ball.png");
	textures["MAGNET"].loadFromFile(ITEMS_DIRECTORY + "Magnet.png");
	textures["AIR_SNEAKERS"].loadFromFile(ITEMS_DIRECTORY + "Air Sneakers.png");
	textures["SHIELD"].loadFromFile(ITEMS_DIRECTORY + "Shield.png");
	textures["FLYING_NIMBUS"].loadFromFile(ITEMS_DIRECTORY + "Flying Nimbus.png");
	textures["SUPER_MUSHROOM"].loadFromFile(ITEMS_DIRECTORY + "Super Mushroom.png");
	textures["FIRE_FLOWER"].loadFromFile(ITEMS_DIRECTORY + "Fire Flower.png");
	textures["POWER_UP_BORDER"].loadFromFile(ITEMS_DIRECTORY + "Border.png");

	textures["SHIELD_EFFECT"].loadFromFile(ITEMS_DIRECTORY + "Shield Effect.png");
	textures["FLYING_NIMBUS_EFFECT"].loadFromFile(ITEMS_DIRECTORY + "Flying Nimbus Effect.png");
	textures["MAGNET_EFFECT"].loadFromFile(ITEMS_DIRECTORY + "Magnet Effect.png");
	textures["AIR_SNEAKERS_EFFECT"].loadFromFile(ITEMS_DIRECTORY + "Air Sneakers Effect.png");

	// Decoration
	textures["EXCLAMATION"].loadFromFile(DECORATIONS_DIRECTORY + "Exclamation.png");

	// Boss
	textures["BOSS"].loadFromFile(ENEMIES_DIRECTORY + "Boss.png");

	// Banzai Bill
	textures["BANZAI_BILL"].loadFromFile(ENEMIES_DIRECTORY + "BanzaiBill.png");

	// all above textures are smooth
	for (auto& t : textures) t.second.setSmooth(true);
	// all below textures are not smooth
	

    // UI
    textures["Welcome Background"].loadFromFile("./Resources/Background/MarioWelcomeIT.png");
    textures["Login Background"] = textures["Welcome Background"];
    textures["Play Background"].loadFromFile("./Resources/Background/Robot.jpg");
    textures["Select Level Background"].loadFromFile("./Resources/Background/EndTime.jpg");
	textures["Victory Background"].loadFromFile("./Resources/Background/Victory.jpg");
}

void Resources::initFonts()
{
    fonts["Standard"].loadFromFile("./Resources/Fonts/Mario.ttf");
	fonts["NewPixel"].loadFromFile("./Resources/Fonts/04B_30__.TTF");
	//fonts["Standard"].loadFromFile("./Resources/Fonts/PixelVietnamese.otf");
}

void Resources::initSounds()
{
	/* Load sounds vào soundBuffers["bla bla"], nhưng khi muốn gọi sound thì sounds["bla bla"].play() nha */
	// Sound Effect
	soundBuffers["MARIO_JUMP"].loadFromFile(SOUNDS_DIRECTORY + "/Sound Effect/jump-small.wav");
	soundBuffers["MARIO_DIE"].loadFromFile(SOUNDS_DIRECTORY + "/Sound Effect/mariodie.wav");
	soundBuffers["MARIO_KICK"].loadFromFile(SOUNDS_DIRECTORY + "/Sound Effect/kick.wav");
	soundBuffers["MARIO_STOMP"].loadFromFile(SOUNDS_DIRECTORY + "/Sound Effect/stomp.wav");
	soundBuffers["POWER_UP_APPEARS"].loadFromFile(SOUNDS_DIRECTORY + "/Sound Effect/powerup-appears.wav");
	soundBuffers["MARIO_COIN"].loadFromFile(SOUNDS_DIRECTORY + "/Sound Effect/coin.wav");
	soundBuffers["MARIO_POWER_UP"].loadFromFile(SOUNDS_DIRECTORY + "/Sound Effect/powerup.wav");
	soundBuffers["MARIO_PIPE"].loadFromFile(SOUNDS_DIRECTORY + "/Sound Effect/pipe.wav");
	soundBuffers["MARIO_FIREBALL"].loadFromFile(SOUNDS_DIRECTORY + "/Sound Effect/fireball.wav");
	soundBuffers["MARIO_1UP"].loadFromFile(SOUNDS_DIRECTORY + "/Sound Effect/1-up.wav");
	soundBuffers["MARIO_BREAK_BLOCK"].loadFromFile(SOUNDS_DIRECTORY + "/Sound Effect/breakblock.wav");
	soundBuffers["SCREAM"].loadFromFile(SOUNDS_DIRECTORY + "/Sound Effect/scream.wav");

	soundBuffers["BOWSER_FIRE"].loadFromFile(SOUNDS_DIRECTORY + "/Sound Effect/bowserfire.wav");

	soundBuffers["GAME_OVER"].loadFromFile(SOUNDS_DIRECTORY + "/Sound Effect/gameover.wav");
	soundBuffers["PAUSE"].loadFromFile(SOUNDS_DIRECTORY + "/Sound Effect/pause.wav");
	soundBuffers["STAGE_CLEAR"].loadFromFile(SOUNDS_DIRECTORY + "/Sound Effect/stage-clear.wav");
	
	// Music

	soundBuffers["MARIO_MAIN_THEME"].loadFromFile(SOUNDS_DIRECTORY + "/Music/Overworld.wav");
	soundBuffers["MARIO_UNDERGROUND"].loadFromFile(SOUNDS_DIRECTORY + "/Music/Underworld.wav");
	soundBuffers["MARIO_WATER"].loadFromFile(SOUNDS_DIRECTORY + "/Music/Underwater.wav");
	soundBuffers["LV3_1"].loadFromFile(SOUNDS_DIRECTORY + "/Music/Lv3_1.wav");
	soundBuffers["LV3_2"].loadFromFile(SOUNDS_DIRECTORY + "/Music/Lv3_2.wav");

	for (auto& s : soundBuffers)
	{
		sounds[s.first].setBuffer(s.second);
	}
}

Resources::Resources()
{
}

Resources::~Resources()
{
}