#pragma once
#include "Component.h"







class FollowPlayer : public Component {
private:

	float followSpeed;
	float detectionRadius;
	
public:
	FollowPlayer(Entity* owner, Entity* player);
	void setEnabled();
	FollowPlayer(Entity* owner, Entity* player, float followSpeed, float detectionRadius);
	void update(float deltaTime) override;
};



class Pace : public Component {
private:

	float paceDistance;
	float paceSpeed;
	sf::Vector2f paceCenter;
public:
	Pace(Entity* owner, Entity * player);
	Pace(Entity* owner, Entity* player, float paceDistance, float paceSpeed, sf::Vector2f paceCenter);
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