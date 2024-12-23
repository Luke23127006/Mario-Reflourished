#pragma once
#include "EnemiesComponent.h"
#include "Enemy.h"






// FOLLOW PLAYER
FollowPlayer::FollowPlayer(Entity* owner, Entity* player) : Component(owner, player)
{
	followSpeed = FOLLOW_SPEED;
	detectionRadius = DETECTION_RADIUS;
	timeWait =3.0f;
	countTime = timeWait;
}


FollowPlayer::FollowPlayer(Entity* owner, Entity* player, float followSpeed) : Component(owner, player), followSpeed(followSpeed)
{
	detectionRadius = DETECTION_RADIUS;
	timeWait = 3.0f;
	countTime = timeWait;
}


FollowPlayer::FollowPlayer(Entity* owner, Entity* player, float followSpeed, float detectionRadius) : Component(owner, player), followSpeed(followSpeed), detectionRadius(detectionRadius)
{
	timeWait = 3.0f;
	countTime = timeWait;
}

FollowPlayer::FollowPlayer(Entity* owner, Entity* player, float followSpeed, float detectionRadius, float timeWait) : Component(owner, player), followSpeed(followSpeed), detectionRadius(detectionRadius), timeWait(timeWait)
{
		countTime = timeWait;
}
void FollowPlayer::setEnabled()
{
	sf::Vector2f playerPosition = player->getPosition();
	sf::Vector2f ownerPosition = owner->getPosition();
	float distance = sqrt(pow(playerPosition.x - ownerPosition.x, 2) + pow(playerPosition.y - ownerPosition.y, 2));
	if (distance < detectionRadius)
	{
		enabled = true;
	}
	else
	{
		enabled = false;
	}
}



void FollowPlayer::update(float deltaTime)
{

	setEnabled();
	if (!enabled) return;

	sf::Vector2f playerPosition = player->getPosition();
	sf::Vector2f ownerPosition = owner->getPosition();
	sf::Vector2f vectorDirection = playerPosition - ownerPosition;


	

	if (countTime > 0)
	{
		
		countTime = std::max(0.f, countTime - deltaTime);
		if (countTime == 0.f)
		{
			countTime = -2.f;
		}
		if (abs(vectorDirection.x) < 10)
		{
			this->owner->setVelocity(sf::Vector2f(0.f, this->owner->getVelocity().y));
		}
		else {
			float direction = vectorDirection.x > 0 ? 1 : -1;

			owner->setVelocity(sf::Vector2f(followSpeed * direction, this->owner->getVelocity().y));
		}
	}
	else {
		if (dynamic_cast<Enemy*>(owner)->isCollide())
		{
			srand(time(NULL));
			int random = rand() % 10;
			int newDirection = random % 2 == 0 ? 1 : -1;
			this->owner->setVelocity(sf::Vector2f(newDirection * followSpeed, this->owner->getVelocity().y));
		}
		countTime = std::min (0.f, countTime + deltaTime);
		if (countTime == 0.f)
		{
			countTime = timeWait;
		}
		
	}
	
	

	

}


// PACE


Pace::Pace(Entity* owner, Entity* player) : Component(owner, player)
{
	paceDistance = DETECTION_RADIUS;
	paceSpeed = PACE_SPEED;
	paceCenter = owner->getPosition();
}

Pace::Pace(Entity* owner, Entity* player, float paceSpeed): Component(owner, player), paceSpeed(paceSpeed)
{
	paceDistance = DETECTION_RADIUS;
	paceCenter = owner->getPosition();
}
void Pace::setEnabled()
{
	sf::Vector2f playerPosition = player->getPosition();
	sf::Vector2f ownerPosition = owner->getPosition();
	float distance = sqrt(pow(playerPosition.x - ownerPosition.x, 2) + pow(playerPosition.y - ownerPosition.y, 2));
	if (distance > paceDistance)
	{
		enabled = true;
	}
	else
	{
		enabled = false;
	}
}

void Pace::update(float deltaTime)
{
	setEnabled();
	sf::Vector2f thisPosition = owner->getPosition();
	if (dynamic_cast<Enemy*>(owner)->isCollide() && enabled)
	{
		if ((thisPosition.x - paceCenter.x) * this->owner->getVelocity().x >= 0 
			|| abs(thisPosition.x - paceCenter.x) < 10.f) // for epsilon
			owner->setVelocity(sf::Vector2f(-this->owner->getVelocity().x, owner->getVelocity().y));
	
	}
	if (thisPosition.x < paceCenter.x - paceDistance)
	{
		owner->setVelocity(sf::Vector2f(paceSpeed, owner->getVelocity().y));
	}
	else if (thisPosition.x > paceCenter.x + paceDistance)
	{
		owner->setVelocity(sf::Vector2f(-paceSpeed, owner->getVelocity().y));
	}
	else
	{
		if (this->owner->getVelocity().x == 0.f)
		{
			srand(time(NULL));
			int random = rand() % 10;
			int newDirection = random % 2 == 0 ? 1 : -1;
			this->owner->setVelocity(sf::Vector2f(newDirection * paceSpeed, this->owner->getVelocity().y));
		}
		owner->setVelocity(sf::Vector2f(owner->getVelocity().x > 0 ? paceSpeed : -paceSpeed, owner->getVelocity().y));
	}

}


// JUMP



EnemiesJump::EnemiesJump(Entity* owner, Entity* player) : Component(owner, player)
{
	jumpSpeed = ENEMY_JUMP_STRENGHT;
	timeWaitToJump = 0.8;
	countTime = timeWaitToJump;
}

EnemiesJump::EnemiesJump(Entity* owner, Entity* player, float jumpSpeed, float timeWaitToJump) : Component(owner, player), jumpSpeed(jumpSpeed), timeWaitToJump(timeWaitToJump)
{
	countTime = timeWaitToJump;
}

void EnemiesJump::setEnabled()
{
	if (countTime <= 0)
	{
		enabled = true;
	}
	else
	{
		enabled = false;
	}
	
}

void EnemiesJump::update(float deltaTime)
{
	sf::Vector2f playerPosition = player->getPosition();
	sf::Vector2f ownerPosition = owner->getPosition();

	
	if (dynamic_cast<Enemy*>(owner)->isCollide())
	{
		countTime -= deltaTime;
	}
	setEnabled();
	if (!enabled) return;
	owner->setVelocity(sf::Vector2f(owner->getVelocity().x, -jumpSpeed));
	countTime = timeWaitToJump;
}



// PACE FLY








PaceFly::PaceFly(Entity* owner, Entity* player) : Component(owner, player)
{

	paceX = 300;
	paceY = 100;
	paceSpeed = PACE_SPEED;
	angle = 0.0f;
	paceCenter = owner->getPosition() - sf::Vector2f(paceX, 0.f);

}

PaceFly::PaceFly(Entity* owner, Entity* player, float paceX, float paceY, float paceSpeed) : Component(owner, player), paceX(paceX), paceY(paceY), paceSpeed(paceSpeed)
{
	paceCenter = owner->getPosition();
	angle = 0.0f;
}







bool PaceFly::onEllipse()
{
	sf::Vector2f thisPosition = owner->getPosition();
	float dx = thisPosition.x - paceCenter.x;
	float dy = thisPosition.y - paceCenter.y;
	float dx2 = dx * dx;
	float dy2 = dy * dy;
	float a2 = paceX * paceX;
	float b2 = paceY * paceY;
	return abs((dx2 / a2 + dy2 / b2) - 1.f) < 1.0 / 10;
}

void PaceFly::update(float deltaTime)
{

	sf::Vector2f thisPosition = owner->getPosition();

	angle += 2 * PI / 3600;
	if (angle > 2 * PI) angle = 0;
	float targetX = paceCenter.x + paceX * cos(angle);
	float targetY = paceCenter.y + paceY * sin(angle);
	sf::Vector2f VectorDirection = sf::Vector2f(targetX - thisPosition.x, targetY - thisPosition.y);
	sf::Vector2f direction = sf::Vector2f(VectorDirection.x > 0 ? 1 : -1, VectorDirection.y > 0 ? 1 : -1);
	if (dynamic_cast<Enemy*>(owner)->isCollide())
	{
		owner->setVelocity(sf::Vector2f(direction.x * paceSpeed, -paceSpeed / 2));
	}
	else
		owner->setVelocity(sf::Vector2f(direction.x * paceSpeed, direction.y * paceSpeed));
	
	if (this->owner->getVelocity().x == 0.f)
	{
		srand(time(NULL));
		int random = rand() % 10;
		int newDirection = random % 2 == 0 ? 1 : -1;
		this->owner->setVelocity(sf::Vector2f(newDirection * paceSpeed, this->owner->getVelocity().y));
	}
	
}









// BOSS BOWSER


FireAttack::FireAttack(Entity* owner, Entity* player) : Component(owner, player)
{
	cooldownTime = 3.0f;
	countTime = cooldownTime;
	detection_radius = BOWSER_DETECTION_RADIUS;
}

FireAttack::FireAttack(Entity* owner, Entity* player, float detection_radius, float cooldownTime) : Component(owner, player), detection_radius(detection_radius), cooldownTime(cooldownTime)
{
	countTime = cooldownTime / 2;
}

void FireAttack::update(float deltaTime)
{
	sf::Vector2f playerPosition = player->getPosition();
	sf::Vector2f ownerPosition = owner->getPosition();
	sf::Vector2f VectorDirection = sf::Vector2f(playerPosition.x - ownerPosition.x, playerPosition.y - ownerPosition.y);
	sf::Vector2f direction = sf::Vector2f(VectorDirection.x > 0 ? 1 : -1, VectorDirection.y > 0 ? 1 : -1);
	float distance = sqrt(pow(playerPosition.x - ownerPosition.x, 2) + pow(playerPosition.y - ownerPosition.y, 2));
	if (distance < detection_radius)
	{
		countTime -= deltaTime;
		if (countTime <= 0)
		{
			countTime = cooldownTime;
			sf::Vector2f fireBallPosition;
			
			fireBallPosition = sf::Vector2f(ownerPosition.x + owner->getSize().x / 2, ownerPosition.y + owner->getSize().y / 2);
			FireBall* fireBall = new FireBall(
				fireBallPosition,
				sf::Vector2f(FIREBALL_SPEED, FIREBALL_SPEED),
				direction
			);

			fireBalls.push_back(fireBall);
			
			fireBall->setAddressOfWorld(owner->getWorld());
			fireBall->setMap(&owner->getMap());
			owner->addEntity(fireBall);
		}
	}

	for (auto x : fireBalls)
	{
		sf::Vector2f vectorDirectionFireBalls = sf::Vector2f(playerPosition.x - x->getPosition().x, playerPosition.y - x->getPosition().y);
		sf::Vector2f directionFireBalls = sf::Vector2f(vectorDirectionFireBalls.x > 0 ? 1 : -1, vectorDirectionFireBalls.y > 0 ? 1 : -1);
		if (!x->isDying()) x->setDirection(directionFireBalls);
		else fireBalls.erase(std::remove(fireBalls.begin(), fireBalls.end(), x), fireBalls.end());
	}

}