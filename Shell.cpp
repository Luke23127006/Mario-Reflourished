#include "Shell.h"

Shell::Shell(sf::Vector2f position) :
	Entity(sf::Vector2f(KOOPA_SHELL_WIDTH, KOOPA_SHELL_HEIGHT), position),
	activated(false)
{
	this->velocity = sf::Vector2f(0.f, 0.f);
	this->hitbox.setFillColor(sf::Color(64, 128, 64, 255));
	this->hitbox.setPosition(sf::Vector2f(position.x, position.y + KOOPA_HEIGHT - KOOPA_SHELL_HEIGHT));
	animation = new Animation(Resources::textures["KOOPA_SHELL"], 1, 1, sf::Vector2i((int)KOOPA_SHELL_WIDTH, (int)KOOPA_SHELL_HEIGHT));
	this->animation->setPosition(sf::Vector2f(position.x, position.y + KOOPA_HEIGHT - KOOPA_SHELL_HEIGHT));
}

Shell::~Shell()
{
	delete animation;
}

const bool Shell::isActivated() const
{
	return this->activated;
}

void Shell::switchActivation()
{
	this->activated = !this->activated;
	if (this->activated)
	{
		this->velocity = sf::Vector2f(KOOPA_SHELL_SPEED, 0.f);
	}
	else
	{
		this->velocity = sf::Vector2f(0.f, 0.f);
	}
}

void Shell::turnAround()
{
	this->velocity.x = -this->velocity.x;
}

void Shell::update(float deltaTime)
{
	this->hitbox.move(this->velocity * deltaTime);
}