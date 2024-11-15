#include "Decoration.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

Decoration::Decoration(sf::Texture& texture)
{
    this->sprite.setTexture(texture);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    float randomX = static_cast<float>(std::rand() % 800); 
    float randomY = static_cast<float>(std::rand() % 600); 
    this->sprite.setPosition(sf::Vector2f(randomX, randomY));
}

Decoration::~Decoration()
{
}

void Decoration::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}
