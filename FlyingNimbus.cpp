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
	player->velocityMax = sf::Vector2f(NIMBUS_SPEED, NIMBUS_VERTICAL_SPEED);
	this->hitbox.setSize(sf::Vector2f(NIMBUS_WIDTH, NIMBUS_HEIGHT));
	this->hitbox.setFillColor(sf::Color::Yellow);
	this->isAppearing = true;
	this->elapsedTime = 0.0f;
	this->appearTime = 3.0f;
}

FlyingNimbus::FlyingNimbus(sf::Vector2f position) :
	PowerUp(sf::FloatRect(position.x, position.y, TILE_SIZE, TILE_SIZE))
{
	this->duration = NIMBUS_DURATION;
	this->hitbox.setSize(sf::Vector2f(NIMBUS_WIDTH, NIMBUS_HEIGHT));
	this->hitbox.setFillColor(sf::Color::Yellow);
	this->isAppearing = true;
	this->elapsedTime = 0.0f;
	this->appearTime = 3.0f;
}

FlyingNimbus::~FlyingNimbus()
{
	player->velocityMax = sf::Vector2f(PLAYER_SPEED, PLAYER_FALL_SPEED);
}

void FlyingNimbus::getPlayerPosition(sf::Vector2f playerPosition)
{
	this->playerPosition = playerPosition;
}

bool FlyingNimbus::appearing()
{
	return this->isAppearing;
}

float FlyingNimbus::getAppearTime()
{
	return this->appearTime;
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

void FlyingNimbus::appear(float dt)
{
	if (!this->isAppearing) return;
	sf::Vector2f playerPosition = this->player->getPosition();

	this->elapsedTime += dt;
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
	player->acceleration = sf::Vector2f(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		player->acceleration.y = -NIMBUS_ACCELERATION;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		player->acceleration.y = NIMBUS_ACCELERATION;
	}
	else
	{
		player->velocity.y = 0.f;
		player->acceleration.y = 0.f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player->acceleration.x = -NIMBUS_ACCELERATION;
		if (this->velocity.x > 0.f)
		{
			player->acceleration.x += NIMBUS_DECELERATION;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player->acceleration.x = NIMBUS_ACCELERATION;
		if (this->velocity.x < 0.f)
		{
			player->acceleration.x -= NIMBUS_DECELERATION;
		}
	}

	if (player->acceleration.x == 0.f)
	{
		if (this->velocity.x > 0.f)
		{
			player->acceleration.x = std::max(-this->velocity.x / deltaTime, NIMBUS_DECELERATION);
		}
		else if (this->velocity.x < 0.f)
		{
			player->acceleration.x = std::max(this->velocity.x / deltaTime, -NIMBUS_DECELERATION);
		}
	}

	if (this->isAppearing)
	{
		//player->velocity.y -= 50.f;
	}
	std::cout << player->velocity.y << '\n';
}

void FlyingNimbus::update(float deltaTime)
{

	// Appear time
	if (this->isAppearing)
	{
		this->setEnabled(false);
		this->appear(deltaTime);
		return;
	}
	// Use time
	this->setEnabled(true);
	this->duration -= deltaTime;
	//if (this->duration <= 0.f) this->die();
	this->setPosition(this->playerPosition);

}

