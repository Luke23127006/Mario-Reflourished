#include "Plant.h"

Plant::Plant() : Enemy(sf::Vector2f(PLANT_WIDTH, PLANT_HEIGHT), sf::Vector2f(0, 0), 1)
{
	this->hitbox.setSize(sf::Vector2f(PLANT_WIDTH, PLANT_HEIGHT));
	this->hitbox.setPosition(0, 0);
	this->hitbox.setFillColor(sf::Color(0, 0, 0, 120));
	animation = new Animation(Resources::textures["GREEN_PLANT"], 2, 0.08f, sf::Vector2i(PLANT_WIDTH, PLANT_HEIGHT));
	animation->setPosition(sf::Vector2f(0, 0));
	timer = 1.0;
}

Plant::Plant(sf::Vector2f size, sf::Vector2f position) : Enemy(sf::Vector2f(PLANT_WIDTH, PLANT_HEIGHT), position, 1)
{
	this->hitbox.setSize(sf::Vector2f(PLANT_WIDTH, PLANT_HEIGHT));
	this->hitbox.setPosition(position);
	this->hitbox.setFillColor(sf::Color(0, 0, 0, 120));
	animation = new Animation(Resources::textures["GREEN_PLANT"], 2, 0.08f, sf::Vector2i(PLANT_WIDTH, PLANT_HEIGHT));
	animation->setPosition(position);
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
		case PlantState::MOVING_UP:
			if (timer <= 1.5f)
			{
				this->hitbox.move(0.f, -100.f * deltaTime / 1.5f);
			}
			else
			{
				state = PlantState::STAYING;
				timer = 0.f;
			}
			break;

		case PlantState::STAYING:
			if (timer >= 2.f)
			{
				state = PlantState::MOVING_DOWN;
				timer = 0.f;
			}
			break;

		case PlantState::MOVING_DOWN:
			if (timer <= 1.5f)
			{
				this->hitbox.move(0.f, 100.f * deltaTime / 1.5f);
			}
			else
			{
				state = PlantState::MOVING_UP;
				timer = 0.f;
			}
			break;
		}
	}
}

void Plant::takeDamage()
{
}