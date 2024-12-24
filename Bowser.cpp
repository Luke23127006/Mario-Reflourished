#include "Bowser.h"


Bowser::Bowser(sf::Vector2f position) : Enemy(sf::Vector2f(BOWSER_WIDTH, BOWSER_HEIGHT), position, 10)
{

	this->hitbox.setFillColor(sf::Color::Black);
	
}
	

void Bowser::collideWithEntity(Bullet* bullet, Direction from)
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

void Bowser::collideWithEntity(Shell* shell, Direction from)
{
	if (shell->isActivated())
	{
		if (from != Direction::NONE)
		{
			this->health--;
		}
		if (this->health == 0)
		{
			this->die();
			BEAT_BOSS++;
		}	
	}
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

}

Bowser::~Bowser()
{
	
}

