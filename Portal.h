#pragma once

#include "Object.h"

class Portal : public Object
{
private:
	sf::Vector2f destination;

public:
	Portal(sf::Vector2f position, sf::Vector2f destination);
	~Portal();
};

