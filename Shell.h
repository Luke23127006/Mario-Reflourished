#pragma once

#include "Entity.h"
#include "Global.h"
#include "Resources.h"
#include "Animation.h"

class Shell : public Entity
{
private:
	Animation* animation;
	bool activated;
public:
	Shell(sf::Vector2f position);
	virtual ~Shell();

	const bool isActivated() const;
	void switchActivation();
	void turnAround();

	void update(float deltaTime) override;
};

