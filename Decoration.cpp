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

Decoration::~Decoration()
{
}

void Decoration::setScale(sf::Vector2f scale)
{
	this->sprite.setScale(scale);
}

void Decoration::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Decoration::render(sf::RenderTarget& target, sf::Vector2f position)
{
	this->sprite.setPosition(position);
	target.draw(this->sprite);
}
