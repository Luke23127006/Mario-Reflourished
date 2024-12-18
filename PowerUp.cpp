#include "PowerUp.h"
#include "Player.h"

PowerUp::PowerUp(sf::FloatRect container) :
	Entity(sf::Vector2f(POWER_UP_WIDTH, POWER_UP_HEIGHT), sf::Vector2f(container.left, container.top)),
	duration(10.0f),
	container(container)
{
	sf::Vector2f distance = 0.5f * sf::Vector2f(container.width - POWER_UP_WIDTH, container.height - POWER_UP_HEIGHT);
	this->hitbox.move(distance);

	this->animations.push_back(new Animation(Resources::textures["POWER_UPS"], 6, 0.1f, sf::Vector2i(50, 50)));
	this->animations[0]->setSize(sf::Vector2f(POWER_UP_WIDTH, POWER_UP_HEIGHT));
}

PowerUp::~PowerUp()
{
}

const float PowerUp::getDuration() const
{
	return this->duration;
}

void PowerUp::rise(float deltaTime)
{
	this->velocity = sf::Vector2f(0.f, -POWER_UP_RISE_SPEED);
	this->hitbox.move(this->velocity * deltaTime);
}

void PowerUp::turnAround()
{
	this->velocity.x = -this->velocity.x;
}

void PowerUp::collideWithTile(Tile* tile, Direction from)
{
	if (this->velocity.x == 0) return;
	Entity::collideWithTile(tile, from);

	if (from == Direction::LEFT || from == Direction::RIGHT)
	{
		this->turnAround();
	}
	
	if (tile->isHarming() && checkOnGround(this->getGlobalBounds(), tile->getGlobalBounds()))
	{
		this->jump();
	}
}

void PowerUp::collideWithEntity(Entity* entity, Direction& from)
{
	entity->Entity::collideWithEntity(dynamic_cast<Entity*>(this), from);
	entity->collideWithEntity(this, from);
}

void PowerUp::update(float deltaTime)
{
	for (auto& a : this->animations)
	{
		a->update(deltaTime, true);
	}

	if (this->hitbox.getGlobalBounds().intersects(this->container))
	{
		this->rise(deltaTime);
	}
	else
	{
		if (this->onGround) this->velocity.y = 0.f;
		else this->velocity.y += GRAVITY * deltaTime;
		if (this->velocity.x == 0.f)
		{
			this->velocity = sf::Vector2f(POWER_UP_SPEED, 0.f);
		}
		this->move(this->velocity * deltaTime);
	}
}

void PowerUp::applyPowerUp(Player* player)
{
}
