#pragma once
#include <SFML\Graphics.hpp>
#define INT(enumValue) static_cast<int>(enumValue)

#include <string>
#include <ctime>



// Mouse Position
extern sf::Vector2i MOUSE_POSITION;
extern sf::Vector2f MOUSE_VIEW_POSITION;
extern sf::Vector2u WINDOW_SIZE;



const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int ZOOM_LEVEL = 720;

const float GRAVITY = 3000.f;

// colors
const sf::Color PINK = sf::Color(177, 80, 199);
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
const float CAMERA_FOLLOW_DISTANCE = 50.f;
const float CAMERA_SMOOTHING_FACTOR = 5.f;

// player
const float PLAYER_WIDTH = 48.f;
const float PLAYER_HEIGHT = 48.f;
const float PLAYER_BIGGER_HEIGHT = 96.f;
const float PLAYER_MAX_SPEED = 400.f;
const float PLAYER_MAX_FALL_SPEED = 2000.f;
const float PLAYER_ACCELERATION = 800.f;
const float PLAYER_DECELERATION = 1200.f;
const float PLAYER_JUMP_STRENGHT = 550.f;
const float PLAYER_JUMP_TIME = 0.28f;
const float PLAYER_DIE_VELOCITY = 700.f;
const float PLAYER_SHOOT_COOLDOWN = 0.5f;

// bullets
const float BULLET_WIDTH = 10.f;
const float BULLET_HEIGHT = 10.f;
const float BULLET_SPEED = 500.f;
const float BULLET_DURATION = 3.f;

// entities
const float ENTITY_JUMP_STRENGHT = 500.f;

// enemies

const float ENEMY_DIE_TIME = 3.f;
const float ENEMY_DIE_VELOCITY = 400.f;
const float ENEMY_SQUISHED_TIME = 0.5f;

const float GOOMBA_WIDTH = 48.f;
const float GOOMBA_HEIGHT = 48.f;
const float GOOMBA_MAX_SPEED = 200.f;

const float KOOPA_WIDTH = 48.f;
const float KOOPA_HEIGHT = 48.f;
const float KOOPA_MAX_SPEED = 200.f;
const float KOOPA_SHELL_SPEED = 400.f;
const float KOOPA_SHELL_WIDTH = 48.f;
const float KOOPA_SHELL_HEIGHT = 24.f;

const float PLANT_WIDTH = 24.f;
const float PLANT_HEIGHT = 33.f;

const float BANZAI_BILL_WIDTH = 39.f;
const float BANZAI_BILL_HEIGHT = 36.f;

const float BOSS_WIDTH = 69.f;
const float BOSS_HEIGHT = 42.f;

// power up
const float POWER_UP_WIDTH = 50.f;
const float POWER_UP_HEIGHT = 50.f;
const float POWER_UP_RISE_SPEED = 100.f;
const float POWER_UP_SPEED = 200.f;

const float MUSHROOM_DURATION = 5.f;
const float FIRE_FLOWER_DURATION = 5.f;
const float AIR_SNEAKERS_DURATION = 5.f;
const float DOUBLE_COINS_DURATION = 5.f;
const float INVICIBLE_DURATION = 1.f;
const float SHIELD_DURATION = 5.f;
const float MAGNET_DURATION = 5.f;

// tiles
const float TILE_SIZE = 50;
const float TILE_SHAKE_DURATION = 0.25f;
const float TILE_BREAK_DURATION = 3.f;

const float WATER_ACCERATION_REDUCTION = 0.4f;
const float WATER_GRAVITY_REDUCTION = 0.4f;
const float WATER_MAX_SPEED = 280.f;
const float WATER_MIN_VERTICAL_SPEED = 70.f;
const float WATER_MAX_VERTICAL_SPEED = 230.f;

// map
const int MINIMAP_WIDTH = 32;
const int MINIMAP_HEIGHT = 14;

// utilities
void adjustBetween(float& value, float minValue, float maxValue);
int randomize(int l, int r);
std::string encodeString(std::string s);
template <class T, class U>
bool isType(const U& variable) 
{
	return typeid(T) == typeid(variable);
}
template <class T, class U>
bool isDerivedFrom(U& variable)
{
	return dynamic_cast<T*>(&variable) != nullptr;
}

enum class GameState
{
	WELCOME = 0,
	LOGIN,
	PLAY,
	SELECT_CHARACTER,
	SELECT_LEVEL,
	LEVEL1,
	LEVEL2,
	LEVEL3,
	ADVENTURE_MODE,
	ENDLESS_MODE,
	NUM_GAME_STATES,
	EXIT
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
	ACTIVATED = 0,
	COIN,
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
	ENEMY_BARRIER,
	LUCKY_BLOCK,
	BRIGDE,
	PIPE,
	PIPE_TOP_LEFT,
	PIPE_TOP_RIGHT,
	PIPE_BOTTOM_LEFT,
	PIPE_BOTTOM_RIGHT,
	PIPE_DESTINATION,
	SPIKE,
	WATER_BELOW,
	WATER_SURFACE,
	LAVA_BELOW,
	LAVA_SURFACE,
	PORTAL,
	NUM_TILE_TYPES
};

enum class EnemyType
{
	GOOMBA = 1,
	KOOPA,
	NUM_ENEMY_TYPES
};

enum class PipeType
{
	TOP_LEFT = 0,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	NUM_PIPE_TYPES
};

enum class PlantState
{
	MOVING_UP = 0,
	STAYING,
	MOVING_DOWN,
	NUM_PLANT_STATES
};

enum class PlantType
{
	GREEN = 0,
	RED,
	NUM_PLANT_TYPES
};