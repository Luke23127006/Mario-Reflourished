#pragma once
#include "EnemiesComponent.h"
#include "Enemy.h"
#include "Collision.h"
#include "Wukong.h"




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

void PaceFly::setEnabled()
{
	sf::Vector2f playerPosition = player->getPosition();
	sf::Vector2f ownerPosition = owner->getPosition();
	float distance = sqrt(pow(playerPosition.x - ownerPosition.x, 2) + pow(playerPosition.y - ownerPosition.y, 2));
	if (distance > DETECTION_RADIUS)
	{
		enabled = true;
	}
	else
	{
		enabled = false;
	}
}
void PaceFly::update(float deltaTime)
{
	if (enabled && isType<Wukong*>(owner))
	{
		owner->setPosition(paceCenter);
		return;
	}
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
		FIGHT_BOWSER = true;
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
	else
	{
		FIGHT_BOWSER = false;
	}

	for (auto x : fireBalls)
	{
		sf::Vector2f vectorDirectionFireBalls = sf::Vector2f(playerPosition.x - x->getPosition().x, playerPosition.y - x->getPosition().y);
		sf::Vector2f directionFireBalls = sf::Vector2f(vectorDirectionFireBalls.x > 0 ? 1 : -1, vectorDirectionFireBalls.y > 0 ? 1 : -1);
		if (!x->isDying()) x->setDirection(directionFireBalls);
		else fireBalls.erase(std::remove(fireBalls.begin(), fireBalls.end(), x), fireBalls.end());
	}

}






// BOSS WUKONG









Teleport::Teleport(Entity* owner, Entity* player) : Component(owner, player)
{
	speed = WUKONG_FOLLOW_SPEED;
	cooldownTime = 3.0f;
	countTime = cooldownTime;
	detection_radius = WUKONG_DETECTION_RADIUS;
	teleport.resize(4);
	for (auto x : teleport)
	{
		x = false;
	}
	distanceTeleport = 200;
}

Teleport::Teleport(Entity* owner, Entity* player, float speed, float detection_radius, float cooldownTime, float distanceTeleport) : Component(owner, player), speed(speed), detection_radius(detection_radius), cooldownTime(cooldownTime)
{
	countTime = cooldownTime;
	teleport.resize(3);
	for (auto x : teleport)
	{
		x = false;
	}
	this->distanceTeleport = distanceTeleport;
}



void Teleport::setEnabled()
{
	sf::Vector2f playerPosition = player->getPosition();
	sf::Vector2f ownerPosition = owner->getPosition();
	float distance = sqrt(pow(playerPosition.x - ownerPosition.x, 2) + pow(playerPosition.y - ownerPosition.y, 2));
	if (distance < detection_radius)
	{
		enabled = true;
	}
	else
	{
		enabled = false;
	}
}

void Teleport::update(float deltaTime)
{
	setEnabled();
	if (!enabled)
	{
		FIGHT_WUKONG = false;
		return;
	}
	FIGHT_WUKONG = true;
	sf::Vector2f playerPosition = player->getPosition();
	sf::Vector2f ownerPosition = owner->getPosition();
	sf::Vector2f VectorDirection = sf::Vector2f(playerPosition.x - ownerPosition.x, playerPosition.y - ownerPosition.y);
	sf::Vector2f direction = sf::Vector2f(VectorDirection.x > 0 ? 1 : -1, VectorDirection.y > 0 ? 1 : -1);
	if (countTime >= 0)
	{
		owner->setVelocity(sf::Vector2f(direction.x * speed, direction.y * speed));
		countTime -= deltaTime;
	}
	else {
		countTime = cooldownTime;
		std::vector<Entity*> predictObjects(3);
		int XDirection[3] = { 1, -1, 0 };
		int YDirection[3] = { 0, 0, -1 };

		float differenceX = owner->getSize().x - player->getSize().x;
		float differenceY = owner->getSize().y - player->getSize().y + 30;

		// FOR TELEPORTING (predict where to teleport)
		for (int i = 0; i < 3; i++)
		{
			sf::Vector2f predictPosition = playerPosition + sf::Vector2f(XDirection[i] * distanceTeleport, YDirection[i] * distanceTeleport - differenceY);
			predictObjects[i] = new Entity(owner->getSize(), predictPosition);
			Collision::handle_entity_map(predictObjects[i], &owner->getMap());
			if (!owner->getMap().insideMap(predictObjects[i]))
			{

				teleport[i] = false;
				continue;
			}

			if (!predictObjects[i]->isCollide())
			{
				teleport[i] = true;
			}
			else {
				teleport[i] = false;
			}
		}

		for (auto x : teleport)
		{
			std::cout << x << " ";
		}
		std::cout << std::endl;
		// TELEPORTING
		srand(time(NULL));
		int random = rand() % 3;
		if (teleport[random])
		{
			owner->setPosition(playerPosition + sf::Vector2f(XDirection[random] * distanceTeleport, YDirection[random] * distanceTeleport - differenceY));

		}
		else {
			for (int i = 0; i < 3; i++)
			{
				if (teleport[i])
				{

					owner->setPosition(playerPosition + sf::Vector2f(XDirection[i] * distanceTeleport, YDirection[i] * distanceTeleport - differenceY));
					break;
				}
			}
		}
		for (auto x : teleport)
		{
			x = false;
		}
		for (auto x : predictObjects)
		{
			delete x;
		}


	}
}




// MAGIC ROD ATTACK

MagicRodAttack::MagicRodAttack(Entity* owner, Entity* player) : Component(owner, player)
{
	cooldownTime = 3.0f;
	countTime = cooldownTime;
	detection_radius = WUKONG_DETECTION_RADIUS;
}

MagicRodAttack::MagicRodAttack(Entity* owner, Entity* player, float detection_radius, float cooldownTime) : Component(owner, player), detection_radius(detection_radius), cooldownTime(cooldownTime)
{
	countTime = cooldownTime / 2;
}








void MagicRodAttack::update(float deltaTime)
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
	
			
			sf::Vector2f rodPosition = sf::Vector2f(ownerPosition.x + owner->getSize().x / 2, ownerPosition.y + owner->getSize().y / 2);
			
			WukongMagicRod* magicRod = new WukongMagicRod(rodPosition, VectorDirection);
			magicRod ->setAddressOfWorld(owner->getWorld());
			magicRod->setMap(&owner->getMap());
			owner->addEntity(magicRod);

		}
	}
	

	

}





// SHADOW CLONE




ShadowClone::ShadowClone(Entity* owner, Entity* player) : Component(owner, player)
{
	cooldownTime = 3.0f;
	countTime = cooldownTime;
	numClone = 3;
	detection_radius = WUKONG_DETECTION_RADIUS;
	timeExist = 10.0f;
	appearTime = 2.0f;

	deleted = false;
}



ShadowClone::ShadowClone(Entity* owner, Entity* player, float detection_radius, float cooldownTime, float numClone) : Component(owner, player), detection_radius(detection_radius), cooldownTime(cooldownTime), numClone(numClone)
{
	countTime = cooldownTime / 2;
	appearTime = 2.0f;

	timeExist = 10.0f;
	clones.reserve(numClone);
	deleted = false;
}

void ShadowClone::setEnabled()
{
	sf::Vector2f playerPosition = player->getPosition();
	sf::Vector2f ownerPosition = owner->getPosition();
	float distance = sqrt(pow(playerPosition.x - ownerPosition.x, 2) + pow(playerPosition.y - ownerPosition.y, 2));
	if (distance < detection_radius)
	{
		enabled = true;
	}
	else
	{
		enabled = false;
	}

}



void ShadowClone::update(float deltaTime)
{
	setEnabled();
	if (!enabled) return;
	sf::Vector2f playerPosition = player->getPosition();
	sf::Vector2f ownerPosition = owner->getPosition();
	
	

	countTime -= deltaTime;

	if (countTime <= 0)
	{
		// reset

		countTime = cooldownTime;
		deleted = false;
		

		// create clones
		std::vector<std::vector<int>> direction = { {1, 1}, {-1, 1}, {1, -1}, {-1, -1} };
		for (int i = 0; i < numClone; ++i)
		{
			int j = i % 4;
			posClone.push_back(sf::Vector2f(ownerPosition.x + direction[j][0] * 100, ownerPosition.y + direction[j][1] * 100));
		}
		for (int i = 0; i < numClone; ++i)
		{
			std::cout << "Wukong here\n";
			clones.push_back(new Wukong(ownerPosition));
			clones.back()->setAddressOfWorld(owner->getWorld());
			clones.back()->setMap(&owner->getMap());
			owner->addEntity(clones.back());
			existTime.push_back(timeExist);

		}
		shadowCloneBuff();
		
	}

	// Appear
	for (int i = 0; i < clones.size(); ++i)
	{
		if (existTime[i] <= 0)
			continue;
		if (existTime[i] >= timeExist - appearTime)
		{
			clones[i]->move((posClone[i] - clones[i]->getPosition()) / 1000.f);
		}
	}

	// Delete

	for (int i = 0; i < clones.size(); ++i)
	{
		existTime[i] -= deltaTime;
		if (existTime[i] <= 0)
		{
			clones[i]->Entity::die();
			
			deleted = true;
		}
	}
	if (deleted)
	{
		clones.clear();
		posClone.clear();
		existTime.clear();
	}
}














void ShadowClone::shadowCloneBuff()
{
	srand(time(NULL));

	for (auto& x : clones)
	{
		int random = rand() % 5;
		float distanceTeleport = rand() % 300;
		if (distanceTeleport <= 150) distanceTeleport = 150;
		if (random <= 3) random = 3;
		if (x == nullptr) continue;
		dynamic_cast<Enemy*>(x)->addBehavior(std::make_shared<PaceFly>(x, player, WUKONG_PACE_X, WUKONG_PACE_Y, WUKONG_PACE_SPEED));
		dynamic_cast<Enemy*>(x)->addBehavior(std::make_shared<Teleport>(x, player, WUKONG_FOLLOW_SPEED, WUKONG_DETECTION_RADIUS, random, distanceTeleport));
		dynamic_cast<Enemy*>(x)->addBehavior(std::make_shared<MagicRodAttack>(x, player, WUKONG_DETECTION_RADIUS, random * 1.25));
	}
}