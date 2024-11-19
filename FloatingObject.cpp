#include "FloatingObject.h"

FloatingObject::FloatingObject(const sf::Texture& texture, sf::Vector2f position) :
	Decoration(texture),
	expirationTime(FLOATING_OBJECT_EXPIRATION_TIME)
{
	this->velocity = FLOATING_OBJECT_VELOCITY;
	this->sprite.setOrigin(sf::Vector2f(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2));
	this->sprite.setPosition(position);
}

FloatingObject::~FloatingObject()
{
}

const bool FloatingObject::isExpired() const
{
	return this->expirationTime <= 0.f;
}

void FloatingObject::update(float deltaTime)
{
	this->expirationTime = std::max(0.f, this->expirationTime - deltaTime);
	this->sprite.move(0.f, -this->velocity * deltaTime);
}

void FloatingObject::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
