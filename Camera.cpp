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
    // for screen view
    SCREEN_TOP_LEFT = sf::Vector2f(this->position.x - size.x / 2, this->position.y - size.y / 2);
    SCREEN_TOP_RIGHT = sf::Vector2f(this->position.x + size.x / 2, this->position.y - size.y / 2);
    SCREEN_BOTTOM_LEFT = sf::Vector2f(this->position.x - size.x / 2, this->position.y + size.y / 2);
    SCREEN_BOTTOM_RIGHT = sf::Vector2f(this->position.x + size.x / 2, this->position.y + size.y / 2);

	return sf::View(this->position, size);
}

const sf::Vector2f Camera::getPosition() const
{
	return this->position;
}

void Camera::setPosition(sf::Vector2f position)
{
	this->position = position;
}

void Camera::move(sf::Vector2f velocity)
{
	this->position += velocity;
}

void Camera::update(float deltaTime, sf::Vector2f playerPosition)
{
    sf::Vector2f offset = playerPosition - this->position;

    if (std::abs(offset.x) > CAMERA_FOLLOW_DISTANCE)
    {
        velocity.x = (offset.x - CAMERA_FOLLOW_DISTANCE * (offset.x > 0 ? 1 : -1)) * CAMERA_SMOOTHING_FACTOR;
    }
    else
    {
        velocity.x = 0.f;
    }

    if (std::abs(offset.y) > CAMERA_FOLLOW_DISTANCE)
    {
        velocity.y = (offset.y - CAMERA_FOLLOW_DISTANCE * (offset.y > 0 ? 1 : -1)) * CAMERA_SMOOTHING_FACTOR;
    }
    else
    {
        velocity.y = 0.f;
    }

    this->move(this->velocity * deltaTime);
}