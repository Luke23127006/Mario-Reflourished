#pragma once
#include "Component.h"
#include<ctime>
#include<random>
#include<cstdlib>
#include<iostream>
#include <math.h>
#include "FireBall.h"
#include "WukongMagicRod.h"

// Enemy Follow
class FollowPlayer : public Component {
private:

	float followSpeed;
	float detectionRadius;
	float timeWait;
	float countTime;

public:
	FollowPlayer(Entity* owner, Entity* player);
	FollowPlayer(Entity* owner, Entity* player, float followSpeed);
	FollowPlayer(Entity* owner, Entity* player, float followSpeed, float detectionRadius);
	FollowPlayer(Entity* owner, Entity* player, float followSpeed, float detectionRadius, float timeWait);
	void setEnabled();		
	void update(float deltaTime) override;
};


// Enemy Pace
class Pace : public Component {
private:

	float paceDistance;
	float paceSpeed;
	sf::Vector2f paceCenter;
public:
	Pace(Entity* owner, Entity * player);
	Pace(Entity* owner, Entity* player, float paceSpeed);
	void setEnabled();
	void update(float deltaTime) override;
};


// Enemy Jump
class EnemiesJump : public Component {
private:
	float jumpSpeed;
	float timeWaitToJump;
	float countTime;
public:
	EnemiesJump(Entity* owner, Entity* player);
	EnemiesJump(Entity* owner, Entity* player, float jumpSpeed, float timeWaitToJump);
	void setEnabled();
	void update(float deltaTime) override;
};




// Enemy Pace Fly
class PaceFly : public Component {
private:
	sf::Vector2f paceCenter;
	float paceX;
	float paceY;
	float paceSpeed;
	float angle;
	
public:
	PaceFly(Entity* owner, Entity* player);
	PaceFly(Entity* owner, Entity* player, float paceX, float paceY, float paceSpeed);
	bool onEllipse();
	void setEnabled();
	void update(float deltaTime) override;
};





// BOSS Bowser




class FireAttack : public Component {
private:
	std::vector<FireBall*> fireBalls;
	float cooldownTime;
	float countTime;
	float detection_radius;

public:
	FireAttack(Entity* owner, Entity* player);
	FireAttack(Entity* owner, Entity* player, float detection_radius, float cooldownTime);
	void update(float deltaTime) override;
};




// BOSS Wukong









class Teleport : public Component
{
private:
	float speed;
	float cooldownTime;
	float countTime;
	float detection_radius;
	std::vector<bool> teleport;
	float distanceTeleport;

public:
	Teleport(Entity* owner, Entity* player);
	Teleport(Entity* owner, Entity* player, float speed, float detection_radius, float cooldownTime, float distanceTeleport);
	void setEnabled();
	void update(float deltaTime) override;

};



class MagicRodAttack : public Component
{
private:
	float cooldownTime;
	float countTime;
	float detection_radius;
	
public:
	MagicRodAttack(Entity* owner, Entity* player);
	MagicRodAttack(Entity* owner, Entity* player, float detection_radius, float cooldownTime);
	void update(float deltaTime) override;
};






class ShadowClone : public Component
{
private:
	float cooldownTime;
	float countTime;
	float numClone;
	float appearTime;
	float timeExist;
	bool deleted;
	float detection_radius;
	std::vector<Entity*> clones;
	std::vector<float> existTime;
	std::vector<sf::Vector2f> posClone;

public:
	ShadowClone(Entity* owner, Entity* player);
	ShadowClone(Entity* owner, Entity* player, float detection_radius, float cooldownTime, float numClone);
	void update(float deltaTime) override;
	void setEnabled();
	void shadowCloneBuff();
};