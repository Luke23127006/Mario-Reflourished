#include "Plant.h"

Plant::Plant() : Enemy(sf::Vector2f(32, 64), sf::Vector2f(0, 0), 1)
{
	this->hitbox.setSize(sf::Vector2f(32, 64));
	this->hitbox.setOrigin(sf::Vector2f(0, 64));
	this->hitbox.setFillColor(sf::Color(0, 0, 0, 120));
	this->sprite.setTexture(Resources::textures["PLANT"]);
	timer = 1.0;
}

Plant::Plant(sf::Vector2f size, sf::Vector2f position) : Enemy(size, position, 1)
{
	this->hitbox.setSize(sf::Vector2f(32, 64));
	this->hitbox.setOrigin(sf::Vector2f(0, 64));
	this->hitbox.setFillColor(sf::Color(0, 0, 0, 120));
	this->sprite.setTexture(Resources::textures["PLANT"]);
	timer = 1.0;
}


Plant::~Plant()
{
}

void Plant::update(float deltaTime)
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
		timer += deltaTime;
		switch (state)
		{
		case Plant::State::MovingUp:
			if (timer <= 1.5f)
			{
				this->hitbox.move(0.f, -100.f * deltaTime / 1.5f);
			}
			else
			{
				state = State::Staying;
				timer = 0.f;
			}
			break;

		case Plant::State::Staying:
			if (timer >= 2.f)
			{
				state = State::MovingDown;
				timer = 0.f;
			}
			break;

		case Plant::State::MovingDown:
			if (timer <= 1.5f)
			{
				this->hitbox.move(0.f, 100.f * deltaTime / 1.5f);
			}
			else
			{
				state = State::MovingUp;
				timer = 0.f;
			}
			break;
		}
	}
}

void Plant::takeDamage()
{
}