#pragma once
#include "EnemiesComponent.h"
#include "Enemy.h"






// FOLLOW PLAYER
FollowPlayer::FollowPlayer(Entity* owner, Entity* player) : Component(owner, player)
{
	followSpeed = FOLLOW_SPEED;
	detectionRadius = DETECTION_RADIUS;
}


FollowPlayer::FollowPlayer(Entity* owner, Entity* player, float followSpeed, float detectionRadius) : Component(owner, player), followSpeed(followSpeed), detectionRadius(detectionRadius)
{
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
	sf::Vector2f direction = playerPosition - ownerPosition;
	owner->setVelocity(sf::Vector2f(followSpeed * (direction.x > 0 ? 1 : -1), this->owner->getVelocity().y));

}


// PACE


Pace::Pace(Entity* owner, Entity* player) : Component(owner, player)
{
	this->player = player;
	paceDistance = DETECTION_RADIUS;
	paceSpeed = PACE_SPEED;
	paceCenter = owner->getPosition();
}

Pace::Pace(Entity* owner,Entity * player, float paceDistance, float paceSpeed, sf::Vector2f paceCenter) : Component(owner, player), paceDistance(paceDistance), paceSpeed(paceSpeed), paceCenter(paceCenter)
{
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
	sf::Vector2f thisPosition = owner->getPosition();
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
	if (distance < DETECTION_RADIUS && dynamic_cast<Enemy*>(owner)->isCollide())
	{
		timeWaitToJump -= deltaTime;
	}
	setEnabled();
	if (!enabled) return;
	owner->setVelocity(sf::Vector2f(owner->getVelocity().x, -jumpSpeed));
	timeWaitToJump = 0.5;
}