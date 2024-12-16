#pragma once

#include "Entity.h"
#include "EnemiesComponent.h"
#include "Animation.h"
#include "Decoration.h"
#include "Resources.h"
#include "Player.h"

class Enemy : public Entity
{
protected:

	sf::Vector2f playerPosition;

	std::vector<std::shared_ptr<Component>> behaviors;

	int health;
	bool followPlayer = false;
	bool isSquished = false;
	bool isColliding = false;

	Decoration exclamation = Decoration(Resources::textures["EXCLAMATION"]);
public:
	Enemy();
	Enemy(sf::Vector2f size, sf::Vector2f position);
	Enemy(sf::Vector2f size, sf::Vector2f position, int health);
	virtual ~Enemy();

	// Enemy AI
	
	void addBehavior(std::shared_ptr<Component> behavior);
	bool isCollide();
	void setCollide(bool collide);
	void turnAround();
	virtual void die() override;
	virtual void squished();
	virtual void takeDamage();

	void collisionTile(Tile* tile, Direction from) override;

	void collisionEntity(Player* player, Direction from) override;
	void collisionEntity(Shell* shell, Direction from) override;
	void collisionEntity(Bullet* bullet, Direction from) override;

	virtual void update(float deltaTime) override;
	virtual void render(sf::RenderTarget& target) override;
};

