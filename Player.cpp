#include "Player.h"
#include "EntityFactory.h"
#include <iostream>

Player::Player(sf::Vector2f size, sf::Vector2f position) :
	Entity(size, position),
	blinkTimer(0.f),
	velocityMax(sf::Vector2f(PLAYER_SPEED, PLAYER_FALL_SPEED)),
	playerState(PlayerState::IDLE),
	invicibleTimer(0.f),
	jumpTimer(PLAYER_JUMP_TIME),
	numCoins(0),
	lives(3)
{
	this->health = 100;
	this->hitbox.setFillColor(sf::Color(255, 0, 0, 96));

	this->animations = std::vector<Animation*>(INT(PlayerState::NUM_PLAYER_STATES), nullptr);
	animations[INT(PlayerState::IDLE)] = new Animation(Resources::textures["MARIO_IDLE"], 1, 1, sf::Vector2i(42, 48));

	animations[INT(PlayerState::WALK)] = new Animation(Resources::textures["MARIO_WALK"], 3, 0.1f, sf::Vector2i(54, 48));
	animations[INT(PlayerState::WALK)]->setOrigin(sf::Vector2f(6.f, 0.f));

	animations[INT(PlayerState::JUMP)] = new Animation(Resources::textures["MARIO_JUMP"], 1, 1, sf::Vector2i(60, 48));
	animations[INT(PlayerState::JUMP)]->setOrigin(sf::Vector2f(9.f, 3.f));

	animations[INT(PlayerState::SWIM)] = new Animation(Resources::textures["MARIO_SWIM"], 4, 0.1f, sf::Vector2i(54, 48));
	animations[INT(PlayerState::SWIM)]->setOrigin(sf::Vector2f(6.f, 0.f));

	animations[INT(PlayerState::DIE)] = new Animation(Resources::textures["MARIO_DIE"], 1, 1, sf::Vector2i(42, 42));
}

Player::~Player()
{
	while (!this->powerUps.empty())
	{
		delete this->powerUps.back();
		this->powerUps.pop_back();
	}
}

void Player::stopJumping()
{
	this->jumpTimer = 0.f;
}

void Player::takeDamage()
{
	if (this->invicibleTimer > 0.f) return;
	this->health--;
	if (this->health == 0) this->die();
	//else
	//{
	//	this->invicibleTimer = 1.f;
	//}
}

void Player::die()
{
	if (this->lives > 0)
	{
		this->lives--;
		Resources::sounds["MARIO_DIE"].play();
	}
	else
	{
		Resources::sounds["GAME_OVER"].play();
	}
	this->dying = true;
	this->enabled = false;
	this->velocity = sf::Vector2f(0.f, -PLAYER_DIE_VELOCITY);
}

void Player::gainPowerUp(PowerUp* powerUp)
{
	if (this->hasPowerUp(powerUp->getType())) return;
	this->powerUps.push_back(powerUp);
}

void Player::updatePowerUps(float deltaTime)
{
	int counter = 0;
	for (auto& p : this->powerUps)
	{
		p->update(deltaTime);
		p->applyPowerUp(deltaTime);
		if (p->isExpired())
		{
			delete this->powerUps.at(counter);
			this->powerUps.erase(this->powerUps.begin() + counter);
			counter--;
		}
		counter++;
	}
}

void Player::addCoin()
{
	this->numCoins++;
	Resources::sounds["MARIO_COIN"].play();
}

sf::Vector2f Player::getAcceleration()
{
	return this->acceleration;
}

int Player::getHealth()
{
	return this->health;
}

const bool Player::getCanShoot() const
{
	return this->canShoot;
}

std::vector<Coin*>& Player::getCoins()
{
	return *this->coins;
}

void Player::setCanBreakBlocks(bool canBreakBlocks)
{
	this->canBreakBlocks = canBreakBlocks;
}

void Player::setVelocityMax(sf::Vector2f velocityMax)
{
	this->velocityMax = velocityMax;
}

void Player::setAcceleration(sf::Vector2f acceleration)
{
	this->acceleration = acceleration;
}

void Player::setHealth(int health)
{
	this->health = health;
}

void Player::setJumpTimerMax(float jumpTimerMax)
{
	this->jumpTimerMax = jumpTimerMax;
}

void Player::setCanShoot(bool canShoot)
{
	this->canShoot = canShoot;
}

void Player::setCoins(std::vector<Coin*>* coins)
{
	this->coins = coins;
}

const bool Player::hasPowerUp(PowerUpType type) const
{
	for (auto& p : this->powerUps)
	{
		if (p->getType() == type) return true;
	}
	return false;
}

void Player::collideWithTile(Tile* tile, Direction from)
{
	Entity::collideWithTile(tile, from);

	if (tile->isSolid())
	{
		switch (from)
		{
		case Direction::LEFT: case Direction::RIGHT:
			this->velocity.x = 0.f;
			break;
		case Direction::UP:
			this->jumpTimer = 0.f;
			break;
		case Direction::DOWN:
			if (this->underWater) break;
			this->jumpTimer = 0.f;
			if (tile->isBreakable() && this->canBreakBlocks)
				tile->seftBreak();
			else
				tile->shake();
			break;
		}
	}
}

void Player::collideWithTile(LuckyBlock* tile, Direction from)
{
}

void Player::collideWithTile(Portal* portal, Direction from)
{
	if (this->getGlobalBounds().left > portal->getGlobalBounds().left)
	{
		this->setPosition(portal->getDestination() + sf::Vector2f(0.f, portal->getGlobalBounds().height - this->getGlobalBounds().height));
	}
}

// Collion ENEMY
void Player::collideWithEntity(Enemy* enemy, Direction from)
{
	if (from == Direction::UP)
	{
		this->velocity.y = -PLAYER_JUMP_STRENGHT / 2;
		enemy->squished();
		Resources::sounds["MARIO_STOMP"].play();
	}
	else if (from != Direction::NONE)
	{
		this->takeDamage();
	}
}

// Collision FIREBALL
void Player::collideWithEntity(FireBall* fireBall, Direction from)
{
	if (from != Direction::NONE)
	{
		this->die();
		fireBall->die();
	}
}

// Collision SHELL
void Player::collideWithEntity(Shell* shell, Direction from)
{
	sf::FloatRect playerBounds = this->getGlobalBounds();
	sf::FloatRect shellBounds = shell->getGlobalBounds();
	if (from == Direction::UP)
	{
		Resources::sounds["MARIO_STOMP"].play();
		this->setPosition(sf::Vector2f(this->getPosition().x, shellBounds.top - playerBounds.height));
		this->velocity.y = -PLAYER_JUMP_STRENGHT / 2;
		shell->switchActivation();
		if (shell->isActivated())
		{
			if (playerBounds.left + playerBounds.width / 2 < shellBounds.left + shellBounds.width / 2)
			{
				shell->setVelocity(sf::Vector2f(KOOPA_SHELL_SPEED, 0.f));
			}
			else
			{
				shell->setVelocity(sf::Vector2f(-KOOPA_SHELL_SPEED, 0.f));
			}
		}
	}
	else if (!shell->isActivated())
	{
		if (from == Direction::LEFT)
		{
			Resources::sounds["MARIO_KICK"].play();
			shell->switchActivation();
			this->setPosition(sf::Vector2f(shellBounds.left - playerBounds.width, this->getPosition().y));
			shell->setVelocity(sf::Vector2f(KOOPA_SHELL_SPEED, 0.f));
		}
		else if (from == Direction::RIGHT)
		{
			Resources::sounds["MARIO_KICK"].play();
			shell->switchActivation();
			this->setPosition(sf::Vector2f(shellBounds.left + shellBounds.width, this->getPosition().y));
			shell->setVelocity(sf::Vector2f(-KOOPA_SHELL_SPEED, 0.f));
		}
	}
	else if (from != Direction::NONE)
	{
		this->die();
	}
}
// Collision POWERUP
void Player::collideWithEntity(PowerUp* powerUp, Direction from)
{
	if (from != Direction::NONE)
	{
		this->gainPowerUp(EntityFactory::createPowerUp(this));
		powerUp->die();
	}
}
// Test FlyingNimbus


void Player::update(float deltaTime)
{
	if (this->isDead())
	{
		this->velocity.y = std::min(this->velocity.y + GRAVITY * deltaTime, PLAYER_FALL_SPEED);
		this->hitbox.move(this->velocity * deltaTime);
	}
	else
	{
		this->updateAcceleration(deltaTime);
		this->updatePowerUps(deltaTime);
		this->updateMovement(deltaTime);
		this->invicibleTimer = std::max(0.f, this->invicibleTimer - deltaTime);
		//Handle nhap nhay
		/*if (this->invicibleTimer - deltaTime > 0.f)
		{
			this->hitbox.setFillColor(this->hitbox.getFillColor().a == 0 ? sf::Color(0, 0, 0, 120) : sf::Color(0, 0, 0, 0));
		}
		else
		{
			this->hitbox.setFillColor(sf::Color(0, 0, 0, 120));
		}*/
	}
	this->updateAnimation(deltaTime);
}

void Player::updateAcceleration(float deltaTime)
{
	// horizontal movement
	this->acceleration = sf::Vector2f(0.f, GRAVITY);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->acceleration.x = -PLAYER_ACCELERATION;
		if (this->velocity.x > 0.f)
		{
			this->acceleration.x += PLAYER_DECELERATION;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->acceleration.x = PLAYER_ACCELERATION;
		if (this->velocity.x < 0.f)
		{
			this->acceleration.x -= PLAYER_DECELERATION;
		}
	}

	if (this->acceleration.x == 0.f)
	{
		if (this->velocity.x > 0.f)
		{
			this->acceleration.x = std::max(-this->velocity.x / deltaTime, PLAYER_DECELERATION);
		}
		else if (this->velocity.x < 0.f)
		{
			this->acceleration.x = std::min(-this->velocity.x / deltaTime, -PLAYER_DECELERATION);
		}
	}

	// vertical movement
	if (!this->onGround)
	{
		this->acceleration.y = GRAVITY;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (this->jumpTimer > 0.f)
			{
				this->acceleration.y = 0.f;
				this->jumpTimer = std::max(this->jumpTimer - deltaTime, 0.f);
			}
		}
	}
	else this->velocity.y = 0.f, this->acceleration.y = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (this->onGround)
		{
			Resources::sounds["MARIO_JUMP"].play();
			this->jumpTimer = this->jumpTimerMax;
			this->acceleration.y = -PLAYER_JUMP_STRENGHT / deltaTime;
			this->onGround = false;
		}
	}
	else this->jumpTimer = 0.f;

	//std::cout << this->acceleration.y << '\n';

	// under water
	/*if (this->underWater)
	{
		acceleration *= 0.5f;
		deceleration /= 0.5f;
		this->velocity.x += acceleration * deltaTime + deceleration * deltaTime;
		adjustBetween(this->velocity.x, -WATER_MAX_SPEED, WATER_MAX_SPEED);

		this->velocity.y = std::max(50.f, this->velocity.y - 2 * GRAVITY * deltaTime);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->velocity.y = -WATER_MAX_VERTICAL_SPEED * 0.9f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			this->velocity.y = std::max(this->velocity.y, WATER_MAX_VERTICAL_SPEED);
		}
	}*/
}

void Player::updateMovement(float deltaTime)
{
	this->velocity += this->acceleration * deltaTime;
	adjustBetween(this->velocity.x, -this->velocityMax.x, this->velocityMax.x);
	adjustBetween(this->velocity.y, -this->velocityMax.y, this->velocityMax.y);
	this->hitbox.move(this->velocity * deltaTime);
}

void Player::updateAnimation(float deltaTime)
{
	this->playerState = PlayerState::IDLE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->playerState = PlayerState::WALK;
		this->flipped = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->playerState = PlayerState::WALK;
		this->flipped = false;
	}
	if (this->velocity.y != 0.f)
	{
		this->playerState = PlayerState::JUMP;
	}
	if (this->underWater) this->playerState = PlayerState::SWIM;

	if (this->dying) this->playerState = PlayerState::DIE;

	for (auto& a : this->animations)
	{
		if (a) a->update(deltaTime, this->flipped);
	}
}



void Player::render(sf::RenderTarget& target)
{
	this->animations[INT(this->playerState)]->render(target, this->hitbox.getPosition());
	for (auto& p : this->powerUps)
	{
		p->render(target);
	}
	Entity::render(target);
}
