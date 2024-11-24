#pragma once

#include "Decoration.h"
#include "Global.h"
#include "Resources.h"

class Cloud : public Decoration
{
private:
	sf::Vector2f velocity;

public:
	Cloud(sf::Vector2f velocity);
	virtual ~Cloud();

	void update(float deltaTime);
};

