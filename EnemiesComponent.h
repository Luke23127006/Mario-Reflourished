#pragma once
#include "Component.h"
#include<ctime>
#include<random>
#include<cstdlib>
#include<iostream>



class FollowPlayer : public Component {
private:

	float followSpeed;
	float detectionRadius;
	float timeWait;

public:
	FollowPlayer(Entity* owner, Entity* player);
	void setEnabled();
	FollowPlayer(Entity* owner, Entity* player, float followSpeed);
	void update(float deltaTime) override;
};



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

class EnemiesJump : public Component {
private:
	float jumpSpeed;
	float timeWaitToJump;
public:
	EnemiesJump(Entity* owner, Entity* player);
	void setEnabled();
	void update(float deltaTime) override;
};