#include "Bullet.h"
#include <iostream>

Bullet::Bullet(sf::Vector2f position, sf::Vector2f velocity)
	: Entity(sf::Vector2f(BULLET_WIDTH, BULLET_HEIGHT), position), 
	duration(2.0f),
	angle(0.f)
{
	this->velocity = velocity;

	this->animations.push_back(new Animation(Resources::textures["BULLET"], 1, 0.1f, sf::Vector2i(48, 48)));
	this->animations[0]->setOrigin(0.5f * this->animations[0]->getSize());
	this->animations[0]->setSize(sf::Vector2f(BULLET_WIDTH * 48 / 42, BULLET_HEIGHT * 48 / 42));
}

Bullet::~Bullet()
{
}

void Bullet::bounce()
{
	this->velocity.y = -500.f;
}

bool Bullet::isExpired()
{
	return this->duration <= 0.f;
}

void Bullet::update(float deltaTime)
{
	if (!this->dying)
	{
		for (auto& a : this->animations)
		{
			a->update(deltaTime, this->velocity.x < 0.f);
			a->setRotation(this->angle += this->velocity.x * deltaTime);
		}

		this->duration -= deltaTime;
		if (this->duration <= 0.f) this->die();
		this->velocity.y += GRAVITY * deltaTime;
		this->hitbox.move(this->velocity * deltaTime);
	}
}

void Bullet::render(sf::RenderTarget& target)
{
	for (auto& a : this->animations)
	{
		a->render(target, this->hitbox.getPosition() + 0.5f * this->hitbox.getSize());
	}
}
