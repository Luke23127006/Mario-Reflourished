#pragma once

#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Shell.h"
#include "PowerUp.h"
#include "Bullet.h"
#include "Bird.h"
#include "Mushroom.h"
#include "Shield.h"
#include "FlyingNimbus.h"

#include <ctime>

class EntityFactory
{
public:
	static Player* createPlayer(sf::Vector2f position);
	static Entity* createGoomba(sf::Vector2f position);
	static Entity* createKoopa(sf::Vector2f position);
	static Entity* createShell(sf::Vector2f position);
	static Entity* createPowerUp(sf::FloatRect container, PowerUpType type);
	static PowerUp* createPowerUp(sf::FloatRect containner);
	static PowerUp* createPowerUp(Player* player);
};