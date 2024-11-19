#pragma once

#define INT(enumValue) static_cast<int>(enumValue)

#include<string>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int ZOOM_LEVEL = 720;

const int TILE_SIZE = 50;

const float GRAVITY = 3000.f;

// directories
const std::string CHARACTERS_DIRECTORY = "./Resources/Characters/Mario/";
const std::string DECORATIONS_DIRECTORY = "./Resources/Decorations/";
const std::string ENEMIES_DIRECTORY = "./Resources/Enemies/";
const std::string FONTS_DIRECTORY = "./Resources/Fonts/";
const std::string ITEMS_DIRECTORY = "./Resources/Items/";
const std::string MAPS_DIRECTORY = "./Resources/Maps/";
const std::string SOUNDS_DIRECTORY = "./Resources/Sounds/";
const std::string TILES_DIRECTORY = "./Resources/Tiles/";

// camera
const float CAMERA_MAX_SPEED = 200.0f;
const float	CAMERA_ACCELERATION = 10.0f;
const float CAMERA_DECELERATION = 10.0f;

// player
const float PLAYER_MAX_SPEED = 400.f;
const float PLAYER_MAX_FALL_SPEED = 2000.f;
const float PLAYER_ACCELERATION = 1000.f;
const float PLAYER_DECELERATION = 1400.f;
const float PLAYER_JUMP_STRENGHT = 1000.f;

// utilities
void adjustBetween(float& value, float minValue, float maxValue);

// decorations
const float FLOATING_OBJECT_VELOCITY = 600.f;
const float FLOATING_OBJECT_EXPIRATION_TIME = 0.2f;

enum class GameState
{
	WELCOME = 0,
	PLAY,
	SELECT_CHARACTER,
	SELECT_LEVEL,
	LEVEL1,
	LEVEL2,
	LEVEL3,
	NUM_GAME_STATES
};

enum class PlayerState
{
	IDLE = 0,
	WALK,
	JUMP,
	DIE,
	NUM_PLAYER_STATES
};

enum class PowerUpType
{
	SHIELD = 0,
	MUSHROOM,
	FIRE_FLOWER,
	MAGNET,
	AIR_SNEAKERS, // double jump
	DOUBLE_COINS,
	INVICIBLE,
	NUM_POWER_UPS
};

enum class LuckyBlockType
{
	COIN = 0,
	POWER_UP,
	RANDOM_POWER_UP,
	NUM_LUCKY_BLOCK_TYPES
};

enum class TileType
{
	EMPTY = 0,
	GROUND_BLOCK,
	GROUND_BLOCK_UNDERGROUND,
	BRICK,
	BRICK_UNDERGROUND,
	BLOCK,
	BLOCK_UNDERGROUND,
	BARRIER,
	LUCKY_BLOCK,
	BRIGDE,
	PIPE,
	SPIKE,
	WATER,
	LAVA,
	NUM_TILE_TYPES
};