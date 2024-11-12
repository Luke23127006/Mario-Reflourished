#pragma once

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int ZOOM_LEVEL = 1;

const int TILE_SIZE = 50;

const float GRAVITY = 980.f;

// camera
const float CAMERA_SPEED = 200.0f;
const float	CAMERA_ACCELERATION = 10.0f;

// player
const float PLAYER_SPEED = 200.0f;
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
	GAME_OVER
};

enum PlayerState
{
	IDLE = 0,
	WALK,
	JUMP,
	SHOOT,
	DIE
};