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
	return new FlyingNimbus(player);
	return new Magnet(player);
	return new FireFlower(player);
	return new Mushroom(player);
	return new AirSneakers(player);
	return new Shield(player);
}

PowerUp* EntityFactory::createPowerUp(Player* player, PowerUpType type, bool infinity)
{
	PowerUp* powerUp = nullptr;
	switch (type)
	{
	case PowerUpType::MUSHROOM:
		powerUp = new Mushroom(player);
		break;
	case PowerUpType::AIR_SNEAKERS:
		powerUp = new AirSneakers(player);
		break;
	case PowerUpType::SHIELD:
		powerUp = new Shield(player);
		break;
	case PowerUpType::FLYING_NIMBUS:
		powerUp = new FlyingNimbus(player);
		break;
	case PowerUpType::FIRE_FLOWER:
		powerUp = new FireFlower(player);
		break;
	case PowerUpType::MAGNET:
		powerUp = new Magnet(player);
		break;
	}

	if (infinity) powerUp->setInfinityDuration();
	return powerUp;
}
