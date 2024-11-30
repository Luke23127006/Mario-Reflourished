#include "Koopa.h"

Koopa::Koopa(sf::Vector2f size, sf::Vector2f position)
	: Enemy(sf::Vector2f(KOOPA_WIDTH, KOOPA_HEIGHT), position)
{
	this->sprite.setTexture(Resources::textures["KOOPA"]);
	this->velocity = sf::Vector2f(KOOPA_MAX_SPEED, 0.f);
	this->hitbox.setFillColor(sf::Color(64, 128, 64, 255));
	this->hitbox.setSize(sf::Vector2f(KOOPA_WIDTH, KOOPA_HEIGHT));
	this->hitbox.setPosition(position);
	animation = new Animation(Resources::textures["KOOPA"], 2, 0.08f, sf::Vector2i(KOOPA_WIDTH, KOOPA_HEIGHT));
}

Koopa::~Koopa()	
{
	delete animation;
}

void Koopa::squished()
{
	Enemy::squished();
	this->dieTimer = 0.f;
}

void Koopa::render(sf::RenderTarget& target)
{
	animation->render(target, this->getPosition());
	target.draw(this->hitbox);
}
