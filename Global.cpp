#include "Global.h"

void adjustBetween(float& value, float minValue, float maxValue)
{
	if (value < minValue) value = minValue;
	if (value > maxValue) value = maxValue;
}

int randomize(int l, int r)
{
	return rand() % (r - l + 1) + l;
}

std::string encodeString(std::string s)
{
	std::string ans = "";
	for (char c : s)
	{
		if ('a' <= c && c <= 'z') ans += c;
		else if ('A' <= c && c <= 'Z') ans += c - 'A' + 'a';
		else ans += ' ';
	}
	return ans;
}

bool checkAbove(sf::FloatRect entityBounds, sf::Vector2f entityLastPosition, sf::FloatRect tileBounds)
{
	if ((entityLastPosition.x + entityBounds.width > tileBounds.left && entityLastPosition.x - tileBounds.left <= tileBounds.width) ||
		(entityLastPosition.x + entityBounds.width < tileBounds.left && tileBounds.left - entityLastPosition.x <= entityBounds.width))
	{
		return (floor(entityLastPosition.y + entityBounds.height) <= tileBounds.top);
	}
	return false;
}

bool checkBelow(sf::FloatRect entityBounds, sf::Vector2f entityLastPosition, sf::FloatRect tileBounds)
{
	if ((entityLastPosition.x + entityBounds.width > tileBounds.left && entityLastPosition.x - tileBounds.left <= tileBounds.width) ||
		(entityLastPosition.x + entityBounds.width < tileBounds.left && tileBounds.left - entityLastPosition.x <= entityBounds.width))
	{
		return ((entityLastPosition.y) >= tileBounds.top + tileBounds.height);
	}
	return false;
}

bool checkOnGround(sf::FloatRect entityBounds, sf::FloatRect tileBounds)
{
	if (entityBounds.left <= tileBounds.left && entityBounds.left + entityBounds.width >= tileBounds.left ||
		entityBounds.left >= tileBounds.left && entityBounds.left <= tileBounds.left + tileBounds.width)
	{
		return (entityBounds.top + entityBounds.height == tileBounds.top);
	}
	return false;
}

sf::Vector2i MOUSE_POSITION;
sf::Vector2f MOUSE_VIEW_POSITION;
sf::Vector2u WINDOW_SIZE;
sf::Vector2f MOUSE_VIEW_LAST_POSITION;

sf::Vector2f SCREEN_BOTTOM_LEFT;
sf::Vector2f SCREEN_BOTTOM_RIGHT;
sf::Vector2f SCREEN_TOP_LEFT;
sf::Vector2f SCREEN_TOP_RIGHT;
sf::Vector2f CAMERA_POSITION;

float ASPECT;
int ZOOM_LEVEL = 720;
float RENDER_DISTANCE = ZOOM_LEVEL + 1000.f;
float UPDATE_DISTANCE = RENDER_DISTANCE + 300.f;

std::string currentMusic = "MARIO_MAIN_THEME";
std::string prevMusic = "NONE";

std::string PLAYER_NAME = "Mario";

float SCORE = 0;
int COINS = 0;
int BEAT_ENEMY = 0;
int BEAT_BOSS = 0;
std::vector<PowerUp*>* POWER_UPS = nullptr;