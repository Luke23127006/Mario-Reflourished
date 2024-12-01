#include "FlyingNimbus.h"
#include <iostream>







FlyingNimbus::FlyingNimbus(sf::Vector2f position) :
	PowerUp(PowerUpType::FLYING_NIMBUS, sf::FloatRect(position.x, position.y, TILE_SIZE, TILE_SIZE))
{	
	this->duration = NIMBUS_DURATION;
	this->hitbox.setSize(sf::Vector2f(NIMBUS_WIDTH, NIMBUS_HEIGHT));
	this->hitbox.setFillColor(sf::Color::Yellow);
	this->isAppearing = true;
	this->elapsedTime = 0.0f;
	this->appearTime = 2.0f;
}

FlyingNimbus::~FlyingNimbus()
{
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


void FlyingNimbus::appear(float dt)
{
	if (this->isAppearing == false) return;
	if (this->elapsedTime >= this->appearTime) {
		this->isAppearing = false;
		this->hitbox.setPosition(playerPosition + sf::Vector2f(0, PLAYER_HEIGHT)); // Đảm bảo vị trí cuối
		return;
	}

	this->elapsedTime += dt;

	// Tỉ lệ thời gian (từ 0 đến 1)
	float t = this->elapsedTime / this->appearTime;

	// Tọa độ ban đầu và cuối
	sf::Vector2f startPosition = playerPosition + sf::Vector2f(300, -300);
	sf::Vector2f endPosition = playerPosition + sf::Vector2f(0, PLAYER_HEIGHT);

	// Biên độ và tần số của sóng
	float amplitude = 100.0f; // Độ cao sóng (điều chỉnh cho đẹp)
	float frequency = 2.0f;   // Số chu kỳ trong thời gian appearTime

	// Tính toán vị trí theo đường cong sin
	float x = startPosition.x + t * (endPosition.x - startPosition.x);
	float y = startPosition.y + t * (endPosition.y - startPosition.y)
		+ amplitude * std::sin(frequency * 3.14159f * t);

	// Cập nhật vị trí Nimbus
	this->hitbox.setPosition(sf::Vector2f(x, y));
	

}

void FlyingNimbus::render(sf::RenderTarget& target)
{
	if (this->duration <= 0) return;
	target.draw(this->hitbox);
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
	std::cout << "Nimbus position: " << this->getPosition().x << " " << this->getPosition().y << "\n";
}

