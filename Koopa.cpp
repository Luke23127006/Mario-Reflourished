#include "Koopa.h"

Koopa::Koopa(sf::Vector2f position)
	: Enemy(sf::Vector2f(KOOPA_WIDTH, KOOPA_HEIGHT), position)
{
	this->velocity = sf::Vector2f(KOOPA_PACE_SPEED, 0.f);

	this->hitbox.setFillColor(sf::Color(64, 128, 64, 128));
	this->hitbox.setSize(sf::Vector2f(KOOPA_WIDTH, KOOPA_HEIGHT));
	this->hitbox.setPosition(position);

	sf::Vector2f scale(3.f, 3.f);
	this->animations.push_back(new Animation(Resources::textures["KOOPA"], 2, 0.2f, sf::Vector2i(KOOPA_WIDTH / scale.x, KOOPA_HEIGHT / scale.y)));
	this->animations.back()->setScale(scale);
}

Koopa::~Koopa()	
{
}

void Koopa::squished()
{
	Enemy::squished();
	this->dieTimer = 0.f;
}

void Koopa::render(sf::RenderTarget& target)
{
	//this->animations.back()->render(target, this->getPosition());
	target.draw(this->hitbox);
}
