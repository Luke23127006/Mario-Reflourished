#include "Object.h"

Object::Object()
{
	this->hitbox.setSize(sf::Vector2f(50.f, 50.f));
	this->hitbox.setPosition(sf::Vector2f(0.f, 0.f));
	this->hitbox.setFillColor(sf::Color::Red);

	this->enabled = true;
}

Object::Object(sf::Vector2f size,sf::Vector2f position)
{
	this->hitbox.setSize(size);
	this->hitbox.setPosition(position);
	this->hitbox.setFillColor(sf::Color::Red);

	this->enabled = true;
}

Object::~Object()
{
}

const sf::FloatRect Object::getGLobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

void Object::setPosition(sf::Vector2f position)
{
	this->hitbox.setPosition(position);
}

void Object::setOrigin(sf::Vector2f origin)
{
	this->hitbox.setOrigin(origin);
}

void Object::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

void Object::update(float deltaTime)
{
}

void Object::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}