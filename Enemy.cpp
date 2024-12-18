#include "Enemy.h"
#include <iostream>

Enemy::Enemy() :
	Entity(sf::Vector2f(50.f, 50.f), sf::Vector2f(0.f, 0.f)),
	health(1)
{

}

Enemy::Enemy(sf::Vector2f size, sf::Vector2f position) :
	Entity(size, position),
	health(1)
{

}

Enemy::Enemy(sf::Vector2f size, sf::Vector2f position, int health) :
	Entity(size, position),
	health(health)
{

}

Enemy::~Enemy()
{
	while (!this->animations.empty())
	{
		delete this->animations.back();
		this->animations.pop_back();
	}
}

void Enemy::turnAround()
{
	this->velocity.x = -this->velocity.x;
}

void Enemy::setCollide(bool collide)
{
	this->isColliding = collide;
}

bool Enemy::isCollide()
{
	return this->isColliding;
}

void Enemy::die()
{
	this->enabled = false;
	this->dying = true;
	this->dieTimer = ENEMY_DIE_TIME;
	this->velocity = sf::Vector2f(0.f, -ENEMY_DIE_VELOCITY);

	float alpha = -1.f;
	for (auto& a : animations)
	{
		a->setOrigin(sf::Vector2f(0.f, a->getSize().y));
		a->setScale(sf::Vector2f(1.f, alpha));
	}
}

void Enemy::squished()
{
	this->isSquished = true;
	this->enabled = false;
	this->dying = true;
	this->dieTimer = ENEMY_SQUISHED_TIME;
	this->velocity = sf::Vector2f(0.f, 0.f);

	float alpha = 0.3f;
	for (auto& a : animations)
	{
		a->setOrigin(sf::Vector2f(0.f, -a->getSize().y / alpha * (1 - alpha)));
		a->setScale(sf::Vector2f(1.f, alpha));
	}
}

void Enemy::takeDamage()
{
}

void Enemy::collideWithTile(Tile* tile, Direction from)
{
	Entity::collideWithTile(tile, from);

	if (from == Direction::LEFT || from == Direction::RIGHT)
	{
		this->setCollide(true);
	}

	if (tile->isHarming() && checkOnGround(this->getGLobalBounds(), tile->getGLobalBounds()))
	{
		this->die();
	}
}

void Enemy::collideWithEntity(Player* player, Direction from)
{
	player->Entity::collideWithEntity(dynamic_cast<Entity*>(this), from);
	player->collideWithEntity(this, from);
}

void Enemy::collideWithEntity(Shell* shell, Direction from)
{
	if (shell->isActivated())
	{
		if (from != Direction::NONE)
		{
			this->die();
		}
	}
	else if (from == Direction::UP)
	{
		this->setPosition(sf::Vector2f(this->getPosition().x, shell->getGLobalBounds().top - this->getGlobalBounds().height));
	}
	else if (from == Direction::LEFT)
	{
		shell->switchActivation();
		this->setPosition(sf::Vector2f(shell->getGlobalBounds().left - this->getGlobalBounds().width, this->getPosition().y));
		shell->setVelocity(sf::Vector2f(KOOPA_SHELL_SPEED, 0.f));
	}
	else if (from == Direction::RIGHT)
	{
		shell->switchActivation();
		this->setPosition(sf::Vector2f(shell->getGlobalBounds().left + shell->getGlobalBounds().width, this->getPosition().y));
		shell->setVelocity(sf::Vector2f(-KOOPA_SHELL_SPEED, 0.f));
	}
}

void Enemy::collideWithEntity(Bullet* bullet, Direction from)
{
	if (from != Direction::NONE) 
	{
		this->die();
		bullet->die();
	}
}

void Enemy::addBehavior(std::shared_ptr<Component> behavior)
{
	this->behaviors.push_back(behavior);
}

void Enemy::update(float deltaTime)
{

	if (this->dying)
	{
		this->dieTimer = std::max(0.f, this->dieTimer - deltaTime);
		if (!this->isSquished)
		{
			this->velocity.y += GRAVITY * deltaTime;
			this->move(this->velocity * deltaTime);
		}
	}
	else
	{
		for (auto& a : this->animations)
		{
			a->update(deltaTime, this->velocity.x < 0.f);
		}

		// For Gravity
		if (this->onGround) this->velocity.y = 0.f;
		else this->velocity.y += GRAVITY * deltaTime;


		// For All Behaviors
		for (auto behavior : this->behaviors)
		{
			behavior->update(deltaTime);
			if (isType<FollowPlayer>(*behavior))
			{
				this->followPlayer = behavior->isEnabled();
			}
		}
		isColliding = false;

		this->move(this->velocity * deltaTime);
	}
}

void Enemy::render(sf::RenderTarget& target)
{
	Entity::render(target);
	target.draw(this->hitbox);
	if (this->followPlayer)
	{
		this->exclamation.render(target, sf::Vector2f(this->getGlobalBounds().left, this->getGlobalBounds().top - this->getGlobalBounds().height / 2));
	}
}
