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

sf::Vector2i MOUSE_POSITION;
sf::Vector2f MOUSE_VIEW_POSITION;
sf::Vector2u WINDOW_SIZE;