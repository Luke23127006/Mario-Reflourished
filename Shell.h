#pragma once
#include "Entity.h"
#include "Resources.h"
#include "Global.h"

class Shell : public Entity
{
public:
	Shell();
	Shell(sf::Vector2f size, sf::Vector2f position);
	virtual ~Shell();

	void update(float deltaTime) override;
};

