#pragma once

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int ZOOM_LEVEL = 1;

const int TILE_SIZE = 50;

const float GRAVITY = 980.f;

// directories
const std::string CHARACTERS_DIRECTORY = "./Resources/Characters/";
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
const float PLAYER_MAX_SPEED = 200.0f;
const float PLAYER_ACCELERATION = 10.0f;
const float PLAYER_DECELERATION = 10.0f;
const float PLAYER_JUMP_STRENGHT = 300.0f;

enum GameState
{
	HOME = 0,
	SETTING,
	SELECT_CHARACTER,
	SELECT_LEVEL,
	PLAYING,
	PAUSED,
	GAME_OVER,
	END_FLAG
};

enum PlayerState
{
	IDLE = 0,
	WALK,
	JUMP,
	SHOOT,
	DIE,
	END_FLAG
};

enum PowerUpType
{
	SHIELD = 0,
	MUSHROOM,
	FIRE_FLOWER,
	MAGNET,
	AIR_SNEAKERS, // double jump
	DOUBLE_COINS,
	END_FLAG
};

enum LuckyBlockType
{
	COIN = 0,
	POWER_UP,
	RANDOM_POWER_UP,
	END_FLAG
};

enum TileType
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
	END_FLAG
};