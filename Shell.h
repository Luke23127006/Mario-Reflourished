#pragma once

#include "Entity.h"
#include "Global.h"
#include "Resources.h"
#include "Animation.h"

class Shell : public Entity
{
private:
	bool activated;
	Animation* animation;
public:
	Shell(sf::Vector2f position);
	virtual ~Shell();

	const bool isActivated() const;
	void switchActivation();
	void turnAround();

	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;
};

