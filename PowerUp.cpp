#include "PowerUp.h"

PowerUp::PowerUp(PowerUpType type, sf::FloatRect container) :
	Entity(sf::Vector2f(50, 50), sf::Vector2f(container.left + container.width / 2, container.top + container.height / 2)),
	type(type),
	duration(5.0f),
	container(container)
{
}

PowerUp::~PowerUp()
{
}

PowerUpType PowerUp::getType()
{
	return this->type;
}

void PowerUp::rise(float deltaTime)
{
}

void PowerUp::update(float deltaTime)
{
}
