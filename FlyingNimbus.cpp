#include "FlyingNimbus.h"








FlyingNimbus::FlyingNimbus(sf::Vector2f position) : 
	Entity(sf::Vector2f(NIMBUS_WIDTH, NIMBUS_HEIGHT), position + sf::Vector2f(300, -300)),
	duration (NIMBUS_DURATION)
{	
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

void FlyingNimbus::appear(float dt)
{
	//if (this->elapsedTime >= this->appearTime)
	//{
	//	this->isAppearing = false;
	//	return;
	//}
	//	
	//this->elapsedTime += dt;
	//float curveFactor = -100.0f;
	//float t = elapsedTime / appearTime; // Tỉ lệ thời gian (từ 0 đến 1)
	////float dx = (this->playerPosition.x - this->getLastPosition().x) * dt / appearTime; // Nội suy thay đổi x
	////float dy = ((this->playerPosition.y - this->getLastPosition().y) + curveFactor * 3.1415 * std::cos(3.1415 * t)) * dt / appearTime; // Nội suy thay đổi y

	////this->hitbox.move(sf::Vector2f(dx, dy));
	//  // Tọa độ hiện tại dựa trên tham số hóa
	//float x = this->getLastPosition().x + t * (this->playerPosition.x - this->getLastPosition().x);
	//float y = this->getLastPosition().y + t * (this->playerPosition.y - this->getLastPosition().y)
	//	+ curveFactor * std::sin(3.1415 * t); // Sử dụng sin để tạo đường cong mượt
	if (this->elapsedTime >= this->appearTime) {
		this->isAppearing = false;
		this->hitbox.setPosition(playerPosition); // Đảm bảo vị trí cuối
		return;
	}

	this->elapsedTime += dt;

	// Tỉ lệ thời gian (từ 0 đến 1)
	float t = this->elapsedTime / this->appearTime;

	// Tọa độ ban đầu và cuối
	sf::Vector2f startPosition = playerPosition + sf::Vector2f(300, -300);
	sf::Vector2f endPosition = playerPosition;

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
	if (this->dying) return;
	target.draw(this->hitbox);
}

void FlyingNimbus::update(float deltaTime)
{
	if (this->dying) return;
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
	if (this->duration <= 0.f) this->die();
	this->setPosition(this->playerPosition);

}

