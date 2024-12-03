#include "Bird.h"








Bird::Bird(sf::Vector2f position)
	: Enemy(sf::Vector2f(BIRD_WIDTH, BIRD_HEIGHT), position)
{
	//this->sprite.setTexture(Resources::textures["BIRD"]);
	this->velocity = sf::Vector2f(BIRD_PACE_SPEED, 0.f);
	this->hitbox.setFillColor(sf::Color(200, 250, 100, 255));
	this->hitbox.setSize(sf::Vector2f(BIRD_WIDTH, BIRD_HEIGHT));
	this->hitbox.setPosition(position);
	
}

Bird::~Bird()
{
	
}

void Bird::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
	//target.draw(this->sprite);
}