#pragma once

#include "Global.h"

#include <SFML/Graphics.hpp>
#include <map>

class ColorManager
{
public:
	static std::map<int, std::string> getObject;

	static void initColors();

	ColorManager();
	virtual ~ColorManager();
};

