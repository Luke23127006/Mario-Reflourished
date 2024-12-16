#include "Bird.h"








Bird::Bird(sf::Vector2f position)
	: Enemy(sf::Vector2f(BIRD_WIDTH, BIRD_HEIGHT), position)
{
	//this->sprite.setTexture(Resources::textures["BIRD"]);
	this->velocity = sf::Vector2f(BIRD_PACE_SPEED, 0.f);
	this->hitbox.setFillColor(sf::Color(200, 250, 100, 255));
	this->hitbox.setSize(sf::Vector2f(BIRD_WIDTH, BIRD_HEIGHT));
	this->hitbox.setPosition(position);

	this->animations.resize(2);
	animations[0] = new Animation(Resources::textures["NORMAL_BIRD"], 8, 0.1f, sf::Vector2i(48, 48));
	animations[1] = new Animation(Resources::textures["ANGRY_BIRD"], 8, 0.1f, sf::Vector2i(48, 48));
}

Bird::~Bird()
{
	
}

void Bird::render(sf::RenderTarget& target)
{	
	Enemy::render(target);

	if (this->followPlayer)
		this->animations[1]->render(target, this->hitbox.getPosition());
	else
		this->animations[0]->render(target, this->hitbox.getPosition());
}