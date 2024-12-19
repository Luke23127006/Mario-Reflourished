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

Entity* EntityFactory::createBird(sf::Vector2f position)
{
	return new Bird(position);
}

Entity* EntityFactory::createBowser(sf::Vector2f position)
{
	return new Bowser(position);
}

Entity* EntityFactory::createShell(sf::Vector2f position)
{
	return new Shell(position);
}

Entity* EntityFactory::createPowerUp(sf::FloatRect container, PowerUpType type)
{
	return new PowerUp(container);
}

PowerUp* EntityFactory::createPowerUp(sf::FloatRect containner)
{
	int chance = rand() % 100;
	return new PowerUp(containner);
	//if (chance < 30) return new PowerUp(PowerUpType::MUSHROOM, containner);
	//if (chance < 60) return new PowerUp(PowerUpType::AIR_SNEAKERS, containner);
	//if (chance < 90) return new PowerUp(PowerUpType::SHIELD , containner); // SHIELD
	//return new PowerUp(PowerUpType::FLYING_NIMBUS, containner); // FLYING_NIMBUS
}

PowerUp* EntityFactory::createPowerUp(Player* player)
{
	int chance = rand() % 100;
	return new FireFlower(player);
	if (chance < 50) return new FlyingNimbus(player);
	return new Mushroom(player);
	return new AirSneakers(player);
	return new Shield(player);
}
