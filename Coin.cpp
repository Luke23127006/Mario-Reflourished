#include "Coin.h"

Coin::Coin(sf::Vector2f position)
{
    const sf::Texture& texture = Resources::textures["coin_texture"];
    int totalFrames = 6; 
    float frameDuration = 0.1f; 
    sf::Vector2i frameSize(32, 32);

    this->animation = new Animation(texture, totalFrames, frameDuration, frameSize);
    this->animation->setPosition(position);
}

Coin::~Coin()
{
    delete this->animation;
}