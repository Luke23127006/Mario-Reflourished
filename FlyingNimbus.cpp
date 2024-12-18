#include "FlyingNimbus.h"
#include "Player.h"
#include <iostream>







FlyingNimbus::FlyingNimbus(Player* player) :
	PowerUp(player)
{
	this->player = player;
	this->duration = NIMBUS_DURATION;
	this->type = PowerUpType::FLYING_NIMBUS;

	if (this->player->hasPowerUp(this->type)) return;
	this->player->setVelocityMax(sf::Vector2f(NIMBUS_SPEED, NIMBUS_VERTICAL_SPEED));
	this->hitbox.setSize(sf::Vector2f(NIMBUS_WIDTH, NIMBUS_HEIGHT));
	this->hitbox.setFillColor(sf::Color::Yellow);
	this->isAppearing = true;
	this->elapsedTime = 0.0f;
	this->appearTime = 2.0f;
}

FlyingNimbus::~FlyingNimbus()
{
	this->player->setVelocityMax(sf::Vector2f(PLAYER_SPEED, PLAYER_FALL_SPEED));
}

//
//void FlyingNimbus::appear(float dt)
//{
//	if (this->isAppearing == false) return;
//	if (this->elapsedTime >= this->appearTime) {
//		this->isAppearing = false;
//		 // Đảm bảo vị trí cuối
//		return;
//	}
//
//	this->elapsedTime += dt;
//
//	// Tỉ lệ thời gian (từ 0 đến 1)
//	float t = (this->elapsedTime / this->appearTime);
//
//	// Tọa độ ban đầu và cuối
//	sf::Vector2f startPosition = playerPosition + sf::Vector2f(300, -300);
//	sf::Vector2f endPosition = playerPosition + sf::Vector2f(0, PLAYER_HEIGHT);
//
//	// Biên độ và tần số của sóng
//	float amplitude = 50.0f; // Độ cao sóng (điều chỉnh cho đẹp)
//	float frequency = 3.0f;   // Số chu kỳ trong thời gian appearTime
//
//	// Tính toán vị trí theo đường cong sin
//	float x = startPosition.x + t * (endPosition.x - startPosition.x);
//	float y = startPosition.y + t * (endPosition.y - startPosition.y)
//		+ amplitude * std::sin(frequency * 3.1415923537f * t);
//
//	// Cập nhật vị trí Nimbus
//	//this->hitbox.setPosition(sf::Vector2f(x, y));
//	this->hitbox.move(sf::Vector2f(x, y) - this->hitbox.getPosition());
//
//}
#include <cmath> // Để sử dụng std::sin và std::cos

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
	this->duration -= deltaTime;

	sf::Vector2f position;
	position.x = this->player->getGlobalBounds().left + this->player->getGlobalBounds().width / 2 - this->hitbox.getSize().x / 2;
	position.y = this->player->getGlobalBounds().top + this->player->getGlobalBounds().height - this->hitbox.getSize().y;
	this->setPosition(position);

}
