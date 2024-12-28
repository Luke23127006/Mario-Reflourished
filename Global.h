#pragma once
#include <SFML\Graphics.hpp>
#define INT(enumValue) static_cast<int>(enumValue)

#include <string>
#include <ctime>

#define PI 3.14159265


extern bool VICTORY;
extern std::string USER_NAME;
// Mouse Position
extern sf::Vector2i MOUSE_POSITION;
extern sf::Vector2f MOUSE_VIEW_POSITION;
extern sf::Vector2u WINDOW_SIZE;
extern sf::Vector2f MOUSE_VIEW_LAST_POSITION;

// Screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
extern int ZOOM_LEVEL;
extern float RENDER_DISTANCE;
extern float UPDATE_DISTANCE;
extern float ASPECT;

// Screen in ZOOM

extern sf::Vector2f SCREEN_TOP_LEFT;
extern sf::Vector2f SCREEN_TOP_RIGHT;
extern sf::Vector2f SCREEN_BOTTOM_LEFT;
extern sf::Vector2f SCREEN_BOTTOM_RIGHT;
extern sf::Vector2f CAMERA_POSITION;

// gravity
const float GRAVITY = 3000.f;
const float ANTI_GRAVITY = -GRAVITY;



// Player score
class PowerUp;
extern float SCORE;
extern int COINS;
extern int BEAT_ENEMY;
extern int BEAT_BOSS;
extern std::vector<PowerUp*>* POWER_UPS;

// colors
const sf::Color PINK = sf::Color(177, 80, 199, 180);
// directories
const std::string CHARACTERS_DIRECTORY = "./Resources/Characters/Mario/";
const std::string LUIGI_DIRECTORY = "./Resources/Characters/Luigi/";
const std::string DECORATIONS_DIRECTORY = "./Resources/Decorations/";
const std::string ENEMIES_DIRECTORY = "./Resources/Enemies/";
const std::string FONTS_DIRECTORY = "./Resources/Fonts/";
const std::string ITEMS_DIRECTORY = "./Resources/Items/";
const std::string MAPS_DIRECTORY = "./Resources/Maps/";
const std::string SOUNDS_DIRECTORY = "./Resources/Sound/";
const std::string TILES_DIRECTORY = "./Resources/Tiles/";

//	music
extern std::string currentMusic;
extern std::string prevMusic;

// camera
const float CAMERA_FOLLOW_DISTANCE = 50.f;
const float CAMERA_SMOOTHING_FACTOR = 5.f;

// player
const float PLAYER_WIDTH = 42.f;
const float PLAYER_HEIGHT = 48.f;
const float PLAYER_BIGGER_WIDTH = 48.f;
const float PLAYER_BIGGER_HEIGHT = 96.f;

const float PLAYER_SPEED = 400.f;
const float PLAYER_FALL_SPEED = 2000.f;
const float PLAYER_ACCELERATION = 800.f;
const float PLAYER_DECELERATION = -1200.f;

const float PLAYER_WATER_ACCELERATION = 400.f;
const float PLAYER_WATER_DECELERATION = -2400.f;

const float PLAYER_JUMP_STRENGHT = 550.f;
const float PLAYER_JUMP_TIME = 0.3f;
const float PLAYER_DIE_VELOCITY = 700.f;
const float PLAYER_SHOOT_COOLDOWN = 0.5f;

// Apply for all Characters



// bullets
const float BULLET_WIDTH = 16.f;
const float BULLET_HEIGHT = 16.f;
const float BULLET_SPEED = 500.f;
const float BULLET_DURATION = 3.f;


// entities
const float ENTITY_JUMP_STRENGHT = 500.f;

// enemies
const float ENEMY_DIE_TIME = 3.f;
const float ENEMY_DIE_VELOCITY = 400.f;
const float ENEMY_SQUISHED_TIME = 0.5f;

// GOOMBA
const float GOOMBA_WIDTH = 48.f;
const float GOOMBA_HEIGHT = 48.f;
const float GOOMBA_MAX_SPEED = 200.f;
const float GOOMBA_PACE_SPEED = 150.f;
const float GOOMBA_FOLLOW_SPEED = 250.f;

//KOOPA
const float KOOPA_WIDTH = 48.f;
const float KOOPA_HEIGHT = 48.f;
const float KOOPA_MAX_SPEED = 200.f;
const float KOOPA_PACE_SPEED = 140.f;
const float KOOPA_FOLLOW_SPEED = 200.f;
const float KOOPA_SHELL_SPEED = 400.f;
const float KOOPA_SHELL_WIDTH = 48.f;
const float KOOPA_SHELL_HEIGHT = 24.f;


// BIRD
const float BIRD_WIDTH = 48.f;
const float BIRD_HEIGHT = 48.f;
const float BIRD_PACE_SPEED = 150.f;
const float BIRD_FOLLOW_SPEED = 200.f;
const float BIRD_PACE_X = 300.f;
const float BIRD_PACE_Y = 200.f;
const float BIRD_DETECTION_RADIUS = 600.f;



// BOWSER
const float BOWSER_WIDTH = 100.f;
const float BOWSER_HEIGHT = 100.f;
const float BOWSER_PACE_SPEED = 30.f;
const float BOWSER_FOLLOW_SPEED = 60.f;
const float BOWSER_DETECTION_RADIUS = 1000.f;

// FIREBALL OF BOWSER
const float FIREBALL_WIDTH = 10.f;
const float FIREBALL_HEIGHT = 10.f;
const float FIREBALL_SPEED = 100.f;

// WUKONG
const float WUKONG_WIDTH = 60.f;
const float WUKONG_HEIGHT = 100.f;
const float WUKONG_PACE_SPEED = 100.f;
const float WUKONG_PACE_X = 300.f;
const float WUKONG_PACE_Y = 200.f;
const float WUKONG_FOLLOW_SPEED = 150.f;
const float WUKONG_DETECTION_RADIUS = 1200.f;


// MAGIC ROD
const float MAGIC_ROD_WIDTH = 10.f;
const float MAGIC_ROD_HEIGHT = 10.f;








const float PLANT_WIDTH = 48.f;
const float PLANT_HEIGHT = 48.f;

const float BANZAI_BILL_WIDTH = 39.f;
const float BANZAI_BILL_HEIGHT = 36.f;







// enemies AI

const float PACE_SPEED = 150.f;
const float FOLLOW_SPEED = 220.f;
const float DETECTION_RADIUS = 300.f;
const float ENEMY_JUMP_STRENGHT = 1000.f;

// power up
const float POWER_UP_WIDTH = 40;
const float POWER_UP_HEIGHT = 40.f;
const float POWER_UP_RISE_SPEED = 100.f;
const float POWER_UP_SPEED = 200.f;

// power up duration
const float MUSHROOM_DURATION = 5.f;
const float FIRE_FLOWER_DURATION = 5.f;
const float AIR_SNEAKERS_DURATION = 5.f;
const float DOUBLE_COINS_DURATION = 5.f;
const float INVICIBLE_DURATION = 1.f;
const float SHIELD_DURATION = 10.f;
const float MAGNET_DURATION = 5.f;
const float NIMBUS_DURATION = 10.f;

// nimbus
const float NIMBUS_WIDTH = 100.f;
const float NIMBUS_HEIGHT = 24.f;
const float NIMBUS_SPEED = 1200.f;
const float NIMBUS_VERTICAL_SPEED = 700.f;
const float NIMBUS_ACCELERATION = 600.f;
const float NIMBUS_DECELERATION = -400.f;

// mushroom
const float GROW_WIDTH = 48.f;
const float GROW_HEIGHT = 96.f;

// air sneakers
const float SNEAKERS_JUMP_TIMER = 0.5f;

// magnet
const float MAGNET_RADIUS = 500.f;

// coin
const float COIN_WIDTH = 28.f;
const float COIN_HEIGHT = 28.f;
const float COIN_MAX_SPEED = 2000.f;

// tiles
const float TILE_SIZE = 50;
const float TILE_SHAKE_DURATION = 0.25f;
const float TILE_BREAK_DURATION = 3.f;

const float WATER_ACCELERATION_REDUCTION = 0.4f;
const float WATER_GRAVITY_REDUCTION = 0.3f;
const float WATER_MAX_SPEED = 280.f;
const float WATER_MIN_VERTICAL_SPEED = 70.f;
const float WATER_MAX_VERTICAL_SPEED = 230.f;

// map
const int MINIMAP_WIDTH = 32;
const int MINIMAP_HEIGHT = 14;

// endless map
const float SPIKE_WALL_SPEED = 100.f;
const float SPIKE_WALL_MAX_SPEED = 200.f;
const float SPIKE_WALL_ACCERATION = 0.5f;
const float SPIKE_WALL_WIDTH = 50.f;
const float SPIKE_WALL_HEIGHT = 1000.f;

// utilities
void adjustBetween(float& value, float minValue, float maxValue);
int randomize(int l, int r);
std::string encodeString(std::string s);
bool checkAbove(sf::FloatRect firstBounds, sf::Vector2f firstLastPosition, sf::FloatRect secondBounds);
bool checkBelow(sf::FloatRect firstBounds, sf::Vector2f firstLastPosition, sf::FloatRect secondBounds);
bool checkOnGround(sf::FloatRect firstBounds, sf::FloatRect secondBounds);

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

// enums
enum class Direction
{
	NONE = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NUM_DIRECTIONS
};

enum class GameState
{
	WELCOME = 0,
	LOGIN,
	PLAY,
	SELECT_LEVEL,
	SELECT_CHARACTER,
	HISTORY,
	LEVEL1,
	LEVEL2,
	LEVEL3,
	PAUSE,
	RESUME,
	REPLAY,
	ADVENTURE_MODE,
	ENDLESS_MODE,
	VICTORY,
	NUM_GAME_STATES,
	EXIT,
	NONE
};



enum class ControlMode {
	KEYBOARD,
	MOUSE
};

enum class PlayerState
{
	IDLE = 0,
	WALK,
	JUMP,
	SWIM,
	SHOOT,
	DIE,
	BIG_IDLE,
	BIG_WALK,
	BIG_JUMP,
	BIG_SWIM,
	BIG_SHOOT,
	BIG_DIE,
	NUM_PLAYER_STATES
};

enum class EnemyState

{
	IDLE = 0,
	PACING,
	FOLLOWING,
	DIE,
	SQUISHED,
	NUM_ENEMY_STATES
};

enum class PowerUpType
{
	SHIELD = 0,
	MUSHROOM,
	FIRE_FLOWER,
	MAGNET,
	AIR_SNEAKERS, // double jump
	FLYING_NIMBUS,
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
	VICTORY,
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