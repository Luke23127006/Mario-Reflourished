#include "Coin.h"

Coin::Coin(sf::Vector2f position)
{
    // Assuming Resources is a class that provides access to textures
    const sf::Texture& texture = Resources::textures["coin_texture"];
    int totalFrames = 6; // Example value, set according to your sprite sheet
    float frameDuration = 0.1f; // Example value, set according to your animation speed
    sf::Vector2i frameSize(32, 32); // Example value, set according to your sprite sheet

    this->animation = new Animation(texture, totalFrames, frameDuration, frameSize);
    this->animation->setPosition(position);
}

Coin::~Coin()
{
    delete this->animation;
}