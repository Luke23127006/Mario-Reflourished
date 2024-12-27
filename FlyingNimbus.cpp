#include "FlyingNimbus.h"
#include "Player.h"
#include <iostream>

FlyingNimbus::FlyingNimbus(Player* player) :
	PowerUp(player),
	isAppearing(true),
	appearTime(2.0f),
	elapsedTime(0.0f)
{
	this->player = player;
	this->duration = this->durationMax = NIMBUS_DURATION;
	this->type = PowerUpType::FLYING_NIMBUS;
	this->icon.setTexture(Resources::textures["FLYING_NIMBUS"]);
	this->animations.push_back(new Animation(Resources::textures["FLYING_NIMBUS_EFFECT"], 1, 1.f, sf::Vector2i(100, 24)));
	//this->animations[0]->setCenter();
	this->isBack = false;

	if (this->player->hasPowerUp(this->type)) return;
	this->player->setVelocityMax(sf::Vector2f(NIMBUS_SPEED, NIMBUS_VERTICAL_SPEED));
	this->hitbox.setSize(sf::Vector2f(NIMBUS_WIDTH, NIMBUS_HEIGHT));
	this->hitbox.setFillColor(sf::Color::Yellow);
}

FlyingNimbus::~FlyingNimbus()
{
	this->player->setVelocityMax(sf::Vector2f(PLAYER_SPEED, PLAYER_FALL_SPEED));
}

void FlyingNimbus::appear(float deltaTime)
{
	if (!this->isAppearing) return;
	sf::Vector2f playerPosition;
	playerPosition.x = this->player->getGlobalBounds().left + this->player->getGlobalBounds().width / 2 - this->hitbox.getSize().x / 2;
	playerPosition.y = this->player->getGlobalBounds().top + this->player->getGlobalBounds().height - this->hitbox.getSize().y;

	this->elapsedTime += deltaTime;
	if (this->elapsedTime >= this->appearTime) {
		this->isAppearing = false;
		// makesure the final position
		this->hitbox.setPosition(playerPosition);
		return;
	}

	// Fraction of time (from 0 to 1)
	float t = this->elapsedTime / this->appearTime;


	// Easing function
	float easeT = 1.0f - std::pow(1.0f - t, 3);
	// Coordinates of start and end
	sf::Vector2f startPosition = playerPosition + sf::Vector2f(300, -300);
	sf::Vector2f endPosition = playerPosition;

	// Amplitude and frequency of the wave
	float amplitude = 50.0f;
	float frequency = 3.f;

	// Calculate the position along the sine curve
	float x = startPosition.x + easeT * (endPosition.x - startPosition.x);
	float y = startPosition.y + easeT * (endPosition.y - startPosition.y);


	y += amplitude * std::sin(1.0f * 3.14159265359f * frequency * t);

	// Update the position of the Nimbus
	this->hitbox.move(sf::Vector2f(x, y) - this->hitbox.getPosition());
}

void FlyingNimbus::applyPowerUp(float deltaTime)
{
	if (this->isAppearing)
	{
		player->move(sf::Vector2f(0, -50.f * deltaTime));
	}

	player->setAcceleration(sf::Vector2f(0.f, 0.f));
	sf::Vector2f playerAcceleration = sf::Vector2f(0.f, 0.f);
	sf::Vector2f playerVelocity = player->getVelocity();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		playerAcceleration.y = -NIMBUS_ACCELERATION;
		if (playerVelocity.y > 0.f)
		{
			playerAcceleration.y += NIMBUS_DECELERATION;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		playerAcceleration.y = NIMBUS_ACCELERATION;
		if (playerVelocity.y < 0.f)
		{
			playerAcceleration.y -= NIMBUS_DECELERATION;
		}
	}

	if (playerAcceleration.y == 0.f)
	{
		if (playerVelocity.y > 0.f)
		{
			playerAcceleration.y = std::max(-playerVelocity.y / deltaTime, NIMBUS_DECELERATION);
		}
		else if (playerVelocity.y < 0.f)
		{
			playerAcceleration.y = std::min(-playerVelocity.y / deltaTime, -NIMBUS_DECELERATION);
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		playerAcceleration.x = -NIMBUS_ACCELERATION;
		if (playerVelocity.x > 0.f)
		{
			playerAcceleration.x += NIMBUS_DECELERATION;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		playerAcceleration.x = NIMBUS_ACCELERATION;
		if (playerVelocity.x < 0.f)
		{
			playerAcceleration.x -= NIMBUS_DECELERATION;
		}
	}

	if (playerAcceleration.x == 0.f)
	{
		if (playerVelocity.x > 0.f)
		{
			playerAcceleration.x = std::max(-playerVelocity.x / deltaTime, NIMBUS_DECELERATION);
		}
		else if (playerVelocity.x < 0.f)
		{
			playerAcceleration.x = std::min(-playerVelocity.x / deltaTime, -NIMBUS_DECELERATION);
		}
	}

	this->player->setAcceleration(playerAcceleration);
	this->player->setVelocity(playerVelocity);
	this->player->setVelocityMax(sf::Vector2f(NIMBUS_SPEED, NIMBUS_VERTICAL_SPEED));
}

void FlyingNimbus::update(float deltaTime)
{
	
	// Appear time
	if (this->isAppearing)
	{
		this->appear(deltaTime);
		return;
	}

	// Use time
	if (this->duration != -1) this->duration -= deltaTime;

	sf::Vector2f position;
	position.x = this->player->getGlobalBounds().left + this->player->getGlobalBounds().width / 2 - this->hitbox.getSize().x / 2;
	position.y = this->player->getGlobalBounds().top + this->player->getGlobalBounds().height - this->hitbox.getSize().y;
	this->setPosition(position);

}

void FlyingNimbus::render(sf::RenderTarget& target)
{
	this->animations[0]->render(target, this->hitbox.getPosition());
}
