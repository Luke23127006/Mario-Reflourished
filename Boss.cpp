#include "Boss.h"

Boss::Boss() : Enemy(sf::Vector2f(BOSS_WIDTH, BOSS_HEIGHT), sf::Vector2f(0, 0), 100)
{
	this->sprite.setTexture(Resources::textures["BOSS"]);
	this->hitbox.setSize(sf::Vector2f(BOSS_WIDTH, BOSS_HEIGHT));
	this->hitbox.setPosition(0, 0);
	animation = new Animation(Resources::textures["BOSS"], 1, 1, sf::Vector2i(BOSS_WIDTH, BOSS_HEIGHT));
	animation->setPosition(sf::Vector2f(0, 0));
}

Boss::Boss(sf::Vector2f size,sf::Vector2f position) : Enemy(sf::Vector2f(BOSS_WIDTH, BOSS_HEIGHT), position, 100)
{
	sf::Vector2f size(BOSS_HEIGHT, BOSS_WIDTH);
	this->sprite.setTexture(Resources::textures["BOSS"]);
	this->hitbox.setSize(size);
	this->hitbox.setPosition(position);
	animation = new Animation(Resources::textures["BOSS"], 1, 1, sf::Vector2i(BOSS_WIDTH, BOSS_HEIGHT));
	animation->setPosition(position);
}

Boss::~Boss()
{
	delete animation;
}

void Boss::attack()
{
}

void Boss::update(float deltaTime)
{
}

void Boss::takeDamage()
{
}