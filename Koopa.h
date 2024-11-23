#pragma once
#include "Enemy.h"
#include "Resources.h"
#include "Shell.h"

class Koopa : public Enemy
{
private:
	Shell shell;
public:
	Koopa();
	Koopa(sf::Vector2f size, sf::Vector2f position, int health);
	~Koopa();

	void takeDamage() override;
	void update(float deltaTime) override;
	void dropShell();
};

