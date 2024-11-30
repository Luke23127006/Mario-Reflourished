#include "BanzaiBill.h"

BanzaiBill::BanzaiBill() : Enemy(sf::Vector2f(BANZAI_BILL_WIDTH, BANZAI_BILL_HEIGHT), sf::Vector2f(0, 0), 1)
{
	this->sprite.setTexture(Resources::textures["BANZAI_BILL"]);
	this->hitbox.setSize(sf::Vector2f(BANZAI_BILL_WIDTH, BANZAI_BILL_HEIGHT));
	this->hitbox.setPosition(0, 0);
	animation = new Animation(Resources::textures["BANZAI_BILL"], 1, 1, sf::Vector2i((int)BANZAI_BILL_WIDTH, (int)BANZAI_BILL_HEIGHT));
	animation->setPosition(sf::Vector2f(0, 0));
	timer = 1.0;
}

BanzaiBill::BanzaiBill(sf::Vector2f size,sf::Vector2f position) : Enemy(sf::Vector2f(BANZAI_BILL_WIDTH, BANZAI_BILL_HEIGHT), position, 1)
{
	this->sprite.setTexture(Resources::textures["BANZAI_BILL"]);
	this->hitbox.setSize(sf::Vector2f(BANZAI_BILL_WIDTH, BANZAI_BILL_HEIGHT));
	this->hitbox.setPosition(position);
	animation = new Animation(Resources::textures["BANZAI_BILL"], 1, 1, sf::Vector2i((int)BANZAI_BILL_WIDTH, (int)BANZAI_BILL_HEIGHT));
	animation->setPosition(position);
	timer = 1.0;
}

BanzaiBill::~BanzaiBill()
{
	delete animation;
}

void BanzaiBill::update(float deltaTime)
{
}

void BanzaiBill::takeDamage()
{
}

void BanzaiBill::render(sf::RenderTarget& target)
{
	animation->render(target, this->getPosition());
	target.draw(this->hitbox);
}