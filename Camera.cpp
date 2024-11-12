#include "Camera.h"

Camera::Camera()
{
	this->position = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	this->velocity = sf::Vector2f(0, 0);
}

Camera::~Camera()
{
}

const sf::View Camera::getView(sf::Vector2u windowSize) const
{
	float aspect = float(windowSize.x) / float(windowSize.y);
	sf::Vector2f size;

	if (aspect > 1.f)
	{
		size = sf::Vector2f(ZOOM_LEVEL * aspect, ZOOM_LEVEL);
	}
	else
	{
		size = sf::Vector2f(ZOOM_LEVEL, ZOOM_LEVEL / aspect);
	}
	return sf::View(this->position, size);
}

void Camera::setPosition(sf::Vector2f position)
{
	this->position = position;
}

void Camera::move(sf::Vector2f velocity)
{
	this->position += this->velocity;
}

void Camera::update(float deltaTime, sf::Vector2f playerPosition)
{
}
