#include "BanzaiBill.h"

BanzaiBill::BanzaiBill() : Enemy(sf::Vector2f(32, 32), sf::Vector2f(0, 0), 1)
{
	this->sprite.setTexture(Resources::textures["BANZAI_BILL"]);
	timer = 1.0;
}

BanzaiBill::BanzaiBill(sf::Vector2f size, sf::Vector2f position) : Enemy(size, position, 1)
{
	this->sprite.setTexture(Resources::textures["BANZAI_BILL"]);
	timer = 1.0;
}

BanzaiBill::~BanzaiBill()
{
}

void BanzaiBill::update(float deltaTime)
{
}

void BanzaiBill::takeDamage()
{
}