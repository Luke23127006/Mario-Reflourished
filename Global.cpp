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

sf::Vector2i MOUSE_POSITION;
sf::Vector2f MOUSE_VIEW_POSITION;
sf::Vector2u WINDOW_SIZE;