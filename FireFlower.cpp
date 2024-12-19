#include "FireFlower.h"
#include "Player.h"
#include "Bullet.h"

FireFlower::FireFlower(Player* player) :
	PowerUp(player)
{
	this->type = PowerUpType::FIRE_FLOWER;
	this->duration = FIRE_FLOWER_DURATION;

	this->player->setCanShoot(true);
}

FireFlower::~FireFlower()
{
	this->player->setCanShoot(false);
}

void FireFlower::applyPowerUp(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (player->getCanShoot() == true)
		{
			player->setCanShoot(false);
			sf::Vector2f distance = 0.5f * sf::Vector2f(player->getGlobalBounds().width - BULLET_WIDTH, player->getGlobalBounds().height - BULLET_HEIGHT);
			if (!player->isFlipped()) player->addEntity(new Bullet(player->getPosition() + distance, sf::Vector2f(BULLET_SPEED, 0.f) + player->getVelocity()));
			else player->addEntity(new Bullet(player->getPosition() + distance, sf::Vector2f(-BULLET_SPEED, 0.f) + player->getVelocity()));
		}
	}
	else
	{
		player->setCanShoot(true);
	}
}
