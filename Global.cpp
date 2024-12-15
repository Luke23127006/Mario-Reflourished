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

bool checkAbove(sf::FloatRect firstBounds, sf::Vector2f firstLastPosition, sf::FloatRect secondBounds)
{
	if ((firstLastPosition.x + firstBounds.width > secondBounds.left && firstLastPosition.x - secondBounds.left <= secondBounds.width) ||
		(firstLastPosition.x + firstBounds.width < secondBounds.left && secondBounds.left - firstLastPosition.x <= firstBounds.width))
	{
		return (floor(firstLastPosition.y + firstBounds.height) <= secondBounds.top);
	}
	return false;
}

bool checkBelow(sf::FloatRect firstBounds, sf::Vector2f firstLastPosition, sf::FloatRect secondBounds)
{
	if ((firstLastPosition.x + firstBounds.width > secondBounds.left && firstLastPosition.x - secondBounds.left <= secondBounds.width) ||
		(firstLastPosition.x + firstBounds.width < secondBounds.left && secondBounds.left - firstLastPosition.x <= firstBounds.width))
	{
		return (ceil(firstLastPosition.y) >= secondBounds.top + secondBounds.height);
	}
	return false;
}

bool checkOnGround(sf::FloatRect firstBounds, sf::FloatRect secondBounds)
{
	if (firstBounds.left <= secondBounds.left && firstBounds.left + firstBounds.width >= secondBounds.left ||
		firstBounds.left >= secondBounds.left && firstBounds.left <= secondBounds.left + secondBounds.width)
	{
		return (firstBounds.top + firstBounds.height == secondBounds.top);
	}
	return false;
}

sf::Vector2i MOUSE_POSITION;
sf::Vector2f MOUSE_VIEW_POSITION;
sf::Vector2u WINDOW_SIZE;
sf::Vector2f MOUSE_VIEW_LAST_POSITION;