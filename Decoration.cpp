#include "Decoration.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

Decoration::Decoration(const sf::Texture& texture)
{
	this->sprite.setTexture(texture);

	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	float randomX = static_cast<float>(std::rand() % 800);
	float randomY = static_cast<float>(std::rand() % 600);
	this->sprite.setPosition(sf::Vector2f(randomX, randomY));
}

Decoration::Decoration(const sf::Texture& texture, sf::Vector2f position)
{
	this->sprite.setTexture(texture);
	this->sprite.setPosition(position);
}

Decoration::Decoration(Animation* animation, sf::Vector2f position)
{
	this->sprite.setPosition(position);
	this->animation = animation;
	this->animation->setPosition(position);
}

Decoration::~Decoration()
{
	if (this->animation) delete this->animation;
}

void Decoration::setScale(sf::Vector2f scale)
{
	this->sprite.setScale(scale);
}

void Decoration::setCenter()
{
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	if (this->animation) this->animation->setCenter();
}

void Decoration::update(float deltaTime)
{
	if (this->animation) this->animation->update(deltaTime, false);
}

void Decoration::render(sf::RenderTarget& target)
{
	if (this->animation)
	{
		animation->render(target, this->sprite.getPosition());
		return;
	}
	target.draw(this->sprite);
}

void Decoration::render(sf::RenderTarget& target, sf::Vector2f position)
{
	this->sprite.setPosition(position);
	if (this->animation)
	{
		animation->render(target, position);
		return;
	}
	target.draw(this->sprite);
}
