#include "Particle.h"

Particle::Particle(const sf::Texture& texture, sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration, float duration) :
	Decoration(texture, position),
	velocity(velocity),
	acceleration(acceleration),
	duration(duration)
{
	this->sprite.setOrigin(sf::Vector2f(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2));
	this->sprite.setPosition(position);
}

Particle::~Particle()
{
}

void Particle::setTextureRect(sf::IntRect textureRect)
{
	this->sprite.setTextureRect(textureRect);
}

const bool Particle::isExpired() const
{
	return this->duration <= 0.f;
}

void Particle::update(float deltaTime)
{
	this->duration = std::max(0.f, this->duration - deltaTime);
	this->velocity += this->acceleration * deltaTime;
	this->sprite.move(this->velocity * deltaTime);
}
