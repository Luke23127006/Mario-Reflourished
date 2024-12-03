#pragma once
#include "EnemiesComponent.h"
#include "Enemy.h"






// FOLLOW PLAYER
FollowPlayer::FollowPlayer(Entity* owner, Entity* player) : Component(owner, player)
{
	followSpeed = FOLLOW_SPEED;
	detectionRadius = DETECTION_RADIUS;
	timeWait = 2.0f;
}


FollowPlayer::FollowPlayer(Entity* owner, Entity* player, float followSpeed) : Component(owner, player), followSpeed(followSpeed)
{
	detectionRadius = DETECTION_RADIUS;
	timeWait = 2.0f;
}

FollowPlayer::~FollowPlayer()
{
	delete this->exclamation;
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


	

	if (timeWait > 0)
	{
		
		if (abs(vectorDirection.x) < 100)
		{
			timeWait = std::max(0.f, timeWait - deltaTime);
			if (timeWait == 0)
			{
				timeWait = -2.0f;
			}
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
		srand(time(NULL));
		int random = rand() % 10;
		int newDirection = random % 2 == 0 ? 1 : -1;
		if (abs(this->owner->getVelocity().x) == 0.0f)
		{
			this->owner->setVelocity(sf::Vector2f( newDirection * followSpeed, this->owner->getVelocity().y));
		}
		timeWait = std::min (0.0f, timeWait + deltaTime);
		if (timeWait == 0)
		{
			timeWait = 2.0f;
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
	if (distance < paceDistance)
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
	if (thisPosition.x < paceCenter.x - paceDistance && !enabled)
	{
		owner->setVelocity(sf::Vector2f(paceSpeed, owner->getVelocity().y));
	}
	else if (thisPosition.x > paceCenter.x + paceDistance && !enabled)
	{
		owner->setVelocity(sf::Vector2f(-paceSpeed, owner->getVelocity().y));
	}
	else
	{
		if (owner->getVelocity().x == 0)
		{
			srand(time(NULL));
			int random = rand() % 10;
			int direction = random % 2 == 0 ? 1 : -1;
			owner->setVelocity(sf::Vector2f(paceSpeed * direction, owner->getVelocity().y));
		}
		owner->setVelocity(sf::Vector2f(owner->getVelocity().x, owner->getVelocity().y));
	}

}


// JUMP



EnemiesJump::EnemiesJump(Entity* owner, Entity* player) : Component(owner, player)
{
	jumpSpeed = ENEMY_JUMP_STRENGHT;
	timeWaitToJump = 0.5;
}

void EnemiesJump::setEnabled()
{
	if (timeWaitToJump <= 0)
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

	
	float distance = sqrt(pow(playerPosition.x - ownerPosition.x, 2) + pow(playerPosition.y - ownerPosition.y, 2));
	if (dynamic_cast<Enemy*>(owner)->isCollide())
	{
		timeWaitToJump -= deltaTime;
	}
	setEnabled();
	if (!enabled) return;
	owner->setVelocity(sf::Vector2f(owner->getVelocity().x, -jumpSpeed));
	timeWaitToJump = 0.5;
}