#include "Shell.h"

Shell::Shell(sf::Vector2f position) :
	Entity(sf::Vector2f(KOOPA_SHELL_WIDTH, KOOPA_SHELL_HEIGHT), position),
	activated(false)
{
	this->velocity = sf::Vector2f(0.f, 0.f);
	this->hitbox.setFillColor(sf::Color(64, 128, 64, 255));
	this->hitbox.setPosition(sf::Vector2f(position.x, position.y + KOOPA_HEIGHT - KOOPA_SHELL_HEIGHT));

	this->animations.push_back(new Animation(Resources::textures["KOOPA_SHELL"], 9, 0.1f, sf::Vector2i(KOOPA_SHELL_WIDTH, KOOPA_SHELL_HEIGHT)));
}

Shell::~Shell()
{
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

void Shell::collisionTile(Tile* tile, Direction from)
{
	Entity::collisionTile(tile, from);
	if (from == Direction::LEFT || from == Direction::RIGHT)
	{
		this->turnAround();
	}
	if (tile->isHarming() && checkOnGround(this->getGlobalBounds(), tile->getGlobalBounds()))
	{
		this->jump();
	}
}

void Shell::collisionEntity(Entity* entity, Direction& from)
{
	if (isType<Entity>(*entity)) return;
	entity->Entity::collisionEntity(dynamic_cast<Entity*>(this), from);
	entity->collisionEntity(this, from);
}

void Shell::update(float deltaTime)
{
	
	if (this->activated)
	{
		for (auto& a : this->animations)
		{
			a->update(deltaTime, this->velocity.x > 0.f);
		}
	}
	this->velocity = sf::Vector2f(this->velocity.x > 0 ? this->velocity.x - 0.1f : this->velocity.x + 0.1f, this->velocity.y + GRAVITY * deltaTime);
	this->hitbox.move(this->velocity * deltaTime);
}