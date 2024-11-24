#pragma once

#include "Entity.h"
#include "Resources.h"
#include "Global.h"

class Shell : public Entity
{
private:
	bool activated;
public:
	Shell(sf::Vector2f position);
	virtual ~Shell();

	const bool isActivated() const;
	void switchActivation();
	void turnAround();

	void update(float deltaTime) override;
};

