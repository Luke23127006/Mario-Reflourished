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
		}
	}
	else if (from == Direction::UP)
	{
		this->setPosition(sf::Vector2f(this->getPosition().x, shell->getGLobalBounds().top - this->getGlobalBounds().height));
	}
	else if (from == Direction::LEFT)
	{
		shell->switchActivation();
		this->setPosition(sf::Vector2f(shell->getGlobalBounds().left - this->getGlobalBounds().width, this->getPosition().y));
		shell->setVelocity(sf::Vector2f(0.f, 0.f));
	}
	else if (from == Direction::RIGHT)
	{
		shell->switchActivation();
		this->setPosition(sf::Vector2f(shell->getGlobalBounds().left + shell->getGlobalBounds().width, this->getPosition().y));
		shell->setVelocity(sf::Vector2f(0.f, 0.f));
	}
}

Bowser::~Bowser()
{
	
}

