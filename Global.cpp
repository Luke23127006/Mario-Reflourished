#include "Global.h"

void adjustBetween(float& value, float minValue, float maxValue)
{
	if (value < minValue) value = minValue;
	if (value > maxValue) value = maxValue;
}