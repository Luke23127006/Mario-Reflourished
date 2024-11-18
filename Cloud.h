#pragma once
#include "Resources.h"
#include "Global.h"
#include "Decoration.h"

class Cloud : public Decoration
{
private:
	sf::Vector2f velocity;

public:
	Cloud(sf::Vector2f velocity);
	virtual ~Cloud();

	void update(float deltaTime);
};

