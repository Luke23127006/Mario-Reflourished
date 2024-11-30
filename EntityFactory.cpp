#include "EntityFactory.h"

Player* EntityFactory::createPlayer(sf::Vector2f position)
{
	return new Player(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT), position);
}

Entity* EntityFactory::createGoomba(sf::Vector2f position)
{
	return new Goomba(position);
}

Entity* EntityFactory::createKoopa(sf::Vector2f position)
{
	return new Koopa(position);
}

Entity* EntityFactory::createShell(sf::Vector2f position)
{
	return new Shell(position);
}

Entity* EntityFactory::createPowerUp(sf::FloatRect container, PowerUpType type)
{
	return new PowerUp(type, container);
}

PowerUp* EntityFactory::createPowerUp(sf::FloatRect containner)
{
	//int chance = rand() % 100;
	//if (chance < 40) return new PowerUp(PowerUpType::MUSHROOM, containner);
	//if (chance < 80) return new PowerUp(PowerUpType::AIR_SNEAKERS, containner);
	//return new PowerUp(PowerUpType::SHIELD , containner); // SHIELD
	return new PowerUp(PowerUpType::FLYING_NIMBUS, containner); // FLYING_NIMBUS
}
