#include "Player.h"
#include <iostream>

Player::Player(sf::Vector2f size, sf::Vector2f position) :
	Entity(size, position),
	blinkTimer(0.f),
	playerState(PlayerState::IDLE),
	invicibleTimer(0.f),
	jumpTimer(PLAYER_JUMP_TIME),
	coins(0),
	lives(3),
	powerUpDuration(INT(PowerUpType::NUM_POWER_UPS), 0.f)
{
	this->nimbus = nullptr;
	this->hitbox.setFillColor(sf::Color(0, 0, 0, 120));
	animation.resize(INT(PlayerState::NUM_PLAYER_STATES));
	animation[INT(PlayerState::IDLE)] = new Animation(Resources::textures["MARIO_IDLE"], 1, 1, sf::Vector2i(42, 48));

	animation[INT(PlayerState::WALK)] = new Animation(Resources::textures["MARIO_WALK"], 3, 0.08f, sf::Vector2i(54, 48));
	animation[INT(PlayerState::WALK)]->setOrigin(sf::Vector2f(6.f, 0.f));

	animation[INT(PlayerState::JUMP)] = new Animation(Resources::textures["MARIO_JUMP"], 1, 1, sf::Vector2i(60, 48));
	animation[INT(PlayerState::JUMP)]->setOrigin(sf::Vector2f(9.f, 3.f));

	animation[INT(PlayerState::DIE)] = new Animation(Resources::textures["MARIO_DIE"], 1, 1, sf::Vector2i(42, 42));
}

Player::~Player()
{
	while (!animation.empty())
	{
		delete animation.back();
		animation.pop_back();
	}

	delete this->nimbus;
}

void Player::stopJumping()
{
	this->jumpTimer = 0.f;
}

void Player::die()
{
	if (this->hasPowerUp(PowerUpType::INVICIBLE)) return;
	if (this->hasPowerUp(PowerUpType::SHIELD))
	{
		this->powerUpDuration[INT(PowerUpType::SHIELD)] = 0.f;
		this->powerUpDuration[INT(PowerUpType::INVICIBLE)] = INVICIBLE_DURATION;
		return;
	}
	this->dying = true;
	this->enabled = false;
	this->velocity = sf::Vector2f(0.f, -PLAYER_DIE_VELOCITY);
}

void Player::gainPowerUp(PowerUp& powerUp)
{
	switch (powerUp.getType())
	{
	case PowerUpType::MUSHROOM:
		if (this->powerUpDuration[INT(powerUp.getType())] > 0.f) break;
		this->hitbox.setSize(sf::Vector2f(PLAYER_WIDTH, PLAYER_BIGGER_HEIGHT));
		this->hitbox.move(0.f, PLAYER_HEIGHT - PLAYER_BIGGER_HEIGHT);
		break;

	case PowerUpType::INVICIBLE:
		if (this->powerUpDuration[INT(PowerUpType::INVICIBLE)] > 0.f) break;
		this->invicibleTimer = INVICIBLE_DURATION;
		break;
	// test flying nimbus	
	case PowerUpType::FLYING_NIMBUS:
		if (this->isNimbusActive) break;
		if (this->powerUpDuration[INT(PowerUpType::FLYING_NIMBUS)] > 0.f) break;
		nimbus = new FlyingNimbus(this->getPosition()
			);
		
		break;
	}
	

	this->powerUpDuration[INT(powerUp.getType())] = powerUp.getDuration();
}

void Player::updatePowerUps(float deltaTime)
{
	// mushroom
	if (this->powerUpDuration[INT(PowerUpType::MUSHROOM)] < 0.f)
	{
		this->powerUpDuration[INT(PowerUpType::MUSHROOM)] = 0.f;
		this->hitbox.setSize(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
	}

	// invicible
	if (this->powerUpDuration[INT(PowerUpType::INVICIBLE)] < 0.f)
	{
		this->powerUpDuration[INT(PowerUpType::INVICIBLE)] = 0.f;
		this->invicibleTimer = 0.f;
	}

	if (this->powerUpDuration[INT(PowerUpType::FLYING_NIMBUS)] > 0.f)
	{
		this->isNimbusActive = true;
		if (this->nimbus->appearing())
		{
			float dt = this->nimbus->getAppearTime();
			this->move(sf::Vector2f(0, -PLAYER_JUMP_STRENGHT * 0.5f * deltaTime / dt));
		}
		std::cout << "Player position" << this->getPosition().x << " " << this->getPosition().y << std::endl;
		this->nimbus->getPlayerPosition(this->getPosition());
		this->nimbus->update(deltaTime);

	}
	else {
		//if (this->nimbus) delete this->nimbus;
		this->isNimbusActive = false;
	}
	for (auto& d : this->powerUpDuration)
	{
		if (d >= 0.f) d -= deltaTime;
	}
}
void Player::addCoin()
{
	this->coins++;
}

const bool Player::hasPowerUp(PowerUpType type) const
{
	return this->powerUpDuration[INT(type)] > 0.f;
}

Bullet* Player::shoot()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (this->canShoot == true)
		{
			this->canShoot = false;
			sf::Vector2f distance = 0.5f * sf::Vector2f(this->getGlobalBounds().width - BULLET_WIDTH, this->getGlobalBounds().height - BULLET_HEIGHT);
			if (!this->flipped) return new Bullet(this->getPosition() + distance, sf::Vector2f(BULLET_SPEED, 0.f) + this->velocity);
			return new Bullet(this->getPosition() + distance, sf::Vector2f(-BULLET_SPEED, 0.f) + this->velocity);
		}
	}
	else
	{
		this->canShoot = true;
	}
	return nullptr;
}

// Test FlyingNimbus


void Player::update(float deltaTime)
{
	if (this->isDead())
	{
		this->velocity.y = std::min(this->velocity.y + GRAVITY * deltaTime, PLAYER_MAX_FALL_SPEED);
		this->hitbox.move(this->velocity * deltaTime);
	}
	else
	{
		if (this->isNimbusActive) this->updateMovementNimbus(deltaTime);
		else
			this->updateMovement(deltaTime);
		this->updateAnimation(deltaTime);
		this->updatePowerUps(deltaTime);
		this->invicibleTimer = std::max(0.f, this->invicibleTimer - deltaTime);
		if (this->nimbus)
		{
			this->nimbus->getPlayerPosition(this->getPosition()
				+ sf::Vector2f(0, PLAYER_HEIGHT) - sf::Vector2f(NIMBUS_WIDTH / 3.0f, NIMBUS_HEIGHT));
			this->nimbus->update(deltaTime);
		}
		//Handle nhap nhay
		if (this->invicibleTimer - deltaTime > 0.f)
		{
			this->hitbox.setFillColor(this->hitbox.getFillColor().a == 0 ? sf::Color(0, 0, 0, 120) : sf::Color(0, 0, 0, 0));
		}
		else
		{
			this->hitbox.setFillColor(sf::Color(0, 0, 0, 120));
		}
	}
}

void Player::updateMovementNimbus(float deltaTime)
{
	float acceleration = 0.0f;
	float deceleration = 0.0f;
	if (this->isNimbusActive)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->velocity.y = -PLAYER_JUMP_STRENGHT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->velocity.y = PLAYER_JUMP_STRENGHT;
		}
		else
		{
			this->velocity.y = 0.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			acceleration = -NIMBUS_ACCELERATION;
			if (this->velocity.x > 0.f)
			{
				deceleration = -NIMBUS_DECELERATION;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			acceleration = NIMBUS_ACCELERATION;
			if (this->velocity.x < 0.f)
			{
				deceleration = NIMBUS_DECELERATION;
			}
		}
		
		if (acceleration == 0.f)
		{
			if (this->velocity.x > 0.f)
			{
				deceleration = std::max(-this->velocity.x / deltaTime, -NIMBUS_DECELERATION);
			}
			else if (this->velocity.x < 0.f)
			{
				deceleration = std::min(-this->velocity.x / deltaTime, NIMBUS_DECELERATION);
			}
		}
	}
	this->velocity.x += acceleration * deltaTime + deceleration * deltaTime;
	adjustBetween(this->velocity.x, -NIMBUS_MAX_SPEED, NIMBUS_MAX_SPEED);
	this->hitbox.move(this->velocity * deltaTime);
}
void Player::updateMovement(float deltaTime)
{
	// horizontal movement
	float acceleration = 0.f;
	float deceleration = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		acceleration = -PLAYER_ACCELERATION;
		if (this->velocity.x > 0.f)
		{
			deceleration = -PLAYER_DECELERATION;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		acceleration = PLAYER_ACCELERATION;
		if (this->velocity.x < 0.f)
		{
			deceleration = PLAYER_DECELERATION;
		}
	}
	if (acceleration == 0.f)
	{
		if (this->velocity.x > 0.f)
		{
			deceleration = std::max(-this->velocity.x / deltaTime, -PLAYER_DECELERATION);
		}
		else if (this->velocity.x < 0.f)
		{
			deceleration = std::min(-this->velocity.x / deltaTime, PLAYER_DECELERATION);
		}
	}

	// vertical movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (this->onGround)
		{
			this->jumpTimer = PLAYER_JUMP_TIME;
			if (this->hasPowerUp(PowerUpType::AIR_SNEAKERS)) this->jumpTimer *= 2.f;
			this->velocity.y = -PLAYER_JUMP_STRENGHT;
			this->onGround = false;
		}
	}
	else this->jumpTimer = 0.f;

	if (!this->onGround)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->jumpTimer > 0.f)
		{
			this->velocity.y = -PLAYER_JUMP_STRENGHT;
			this->jumpTimer = std::max(this->jumpTimer - deltaTime, 0.f);
		}
		else this->velocity.y += GRAVITY * deltaTime;
	}
	else this->velocity.y = 0.f;

	this->velocity.x += acceleration * deltaTime + deceleration * deltaTime;
	adjustBetween(this->velocity.x, -PLAYER_MAX_SPEED, PLAYER_MAX_SPEED);

	// under water
	if (this->underWater)
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
	}

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
	if (this->velocity.x == 0.f) this->playerState = PlayerState::IDLE;
	if (this->velocity.y != 0.f)
	{
		this->playerState = PlayerState::JUMP;
	}

	for (auto& a : animation) a->update(deltaTime, this->flipped);
}



void Player::render(sf::RenderTarget& target)
{
	switch (this->playerState)
	{
	case PlayerState::IDLE:
		this->animation[INT(PlayerState::IDLE)]->render(target, this->hitbox.getPosition());
		break;
	case PlayerState::WALK:
		this->animation[INT(PlayerState::WALK)]->render(target, this->hitbox.getPosition());
		break;
	case PlayerState::JUMP:
		this->animation[INT(PlayerState::JUMP)]->render(target, this->hitbox.getPosition());
		break;
	case PlayerState::DIE:
		this->animation[INT(PlayerState::DIE)]->render(target, this->hitbox.getPosition());
		break;
	}
	target.draw(this->hitbox);
	if (this->nimbus && this->isNimbusActive) this->nimbus->render(target);
}
