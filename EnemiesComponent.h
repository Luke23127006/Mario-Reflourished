#pragma once
#include "Component.h"
#include<ctime>
#include<random>
#include<cstdlib>
#include<iostream>
#include <math.h>
#include "FireBall.h"

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
	void update(float deltaTime) override;
};