#include "Object.h"

Object::Object()
{
	this->hitbox.setSize(sf::Vector2f(50.f, 50.f));
	this->hitbox.setPosition(sf::Vector2f(0.f, 0.f));
	this->hitbox.setFillColor(sf::Color::Red);

	this->sprite.setPosition(this->hitbox.getPosition());

	this->enabled = true;
}

Object::Object(sf::Vector2f size,sf::Vector2f position)
{
	this->hitbox.setSize(size);
	this->hitbox.setPosition(position);
	this->hitbox.setFillColor(sf::Color::Red);
	this->hitbox.setOutlineColor(sf::Color::Black);

	this->sprite.setPosition(this->hitbox.getPosition());

	this->enabled = true;
}

Object::~Object()
{
}

const bool Object::getEnabled() const
{
	return this->enabled;
}

sf::Vector2f Object::getPosition() const
{
	return this->hitbox.getPosition();
}

const sf::FloatRect Object::getGLobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

const sf::Vector2f Object::getCenter() const
{
	return sf::Vector2f(this->hitbox.getPosition().x + this->hitbox.getSize().x / 2, this->hitbox.getPosition().y + this->hitbox.getSize().y / 2);
}

void Object::setSize(sf::Vector2f size)
{
	this->hitbox.setSize(size);
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

sf::FloatRect Object::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

void Object::update(float deltaTime)
{
}

void Object::render(sf::RenderTarget& target)
{
	int borderSize = 1;
	sf::RectangleShape border = this->hitbox;
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineThickness(borderSize);
	border.setOrigin(-borderSize, -borderSize);
	border.setSize(sf::Vector2f(this->hitbox.getSize().x - 2 * borderSize, this->hitbox.getSize().y - 2 * borderSize));
	border.setOutlineColor(sf::Color::Blue);
	border.setOutlineColor(sf::Color::Transparent);
	//target.draw(this->hitbox);
	target.draw(this->sprite);
	target.draw(border);
}