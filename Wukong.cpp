#include "Wukong.h"








Wukong::Wukong() : Enemy(sf::Vector2f(WUKONG_WIDTH, WUKONG_HEIGHT), sf::Vector2f(0, 0), 10)
{
	this->hitbox.setFillColor(sf::Color::Black);
}

Wukong::Wukong(sf::Vector2f position) : Enemy(sf::Vector2f(WUKONG_WIDTH, WUKONG_HEIGHT), position, 10)
{
	this->hitbox.setFillColor(sf::Color::Black);
	this->animations.push_back (new Animation(Resources::textures["WUKONG"], 2, 0.3f, sf::Vector2i(WUKONG_WIDTH, WUKONG_HEIGHT)));
}


void Wukong::collideWithEntity(Bullet* bullet, Direction from)
{
	if (from != Direction::NONE)
	{
		this->health -= 1;
		bullet->die();
	}
	if (this->health == 0)
	{
		this->die();
		BEAT_BOSS++;
	}
}

void Wukong::collideWithEntity(Shell* shell, Direction from)
{

	if (from == Direction::UP)
	{
		shell->setVelocity(sf::Vector2f(KOOPA_SHELL_SPEED, -shell->getVelocity().y));
	}
	else if (from == Direction::LEFT)
	{
		if (!shell->isActivated())
			shell->switchActivation();
		shell->setVelocity(sf::Vector2f(+KOOPA_SHELL_SPEED, 0.f));
	}
	else if (from == Direction::RIGHT)
	{
		if (!shell->isActivated())
			shell->switchActivation();
		shell->setVelocity(sf::Vector2f(-KOOPA_SHELL_SPEED, 0.f));
	}
	else if (from == Direction::DOWN)
	{
		if (!shell->isActivated())
			shell->switchActivation();
		shell->setVelocity(sf::Vector2f(KOOPA_SHELL_SPEED, 0.f));
		this->setVelocity(sf::Vector2f(0.f, -200.f));
	}
}

void Wukong::collideWithTile(Lava* lava, Direction from)
{
	if (from != Direction::NONE)
	{
		lava->setShake(true);
		lava->shake();
	}
	else {
		lava->setShake(false);
	}
}



void Wukong::collideWithTile(Tile* tile, Direction from)
{
	Entity::collideWithTile(tile, from);
}

Wukong::~Wukong()
{
}