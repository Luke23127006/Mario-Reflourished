#include "Player.h"
#include <iostream>

Player::Player(sf::Vector2f size, sf::Vector2f position) :
	Entity(size, position),
	playerState(PlayerState::IDLE),
	invicibleTimer(0.f),
	coins(0),
	lives(3)
{
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
	for (auto& a : this->animation)
		delete a;
}

void Player::update(float deltaTime)
{
	this->updateMovement(deltaTime);
	this->updateAnimation(deltaTime);
	this->invicibleTimer = std::max(0.f, this->invicibleTimer - deltaTime);
}

void Player::updateMovement(float deltaTime)
{
	// horizontal movement
	float acceleration = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		acceleration -= PLAYER_ACCELERATION;
		if (this->velocity.x > 0.f) 
		{
			this->velocity.x = std::max(0.f, this->velocity.x - PLAYER_DECELERATION * deltaTime);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		acceleration += PLAYER_ACCELERATION;
		if (this->velocity.x < 0.f)
		{
			this->velocity.x = std::min(0.f, this->velocity.x + PLAYER_DECELERATION * deltaTime);
		}
	}
	if (acceleration == 0.f)
	{
		if (this->velocity.x > 0.f)
		{
			this->velocity.x = std::max(0.f, this->velocity.x - PLAYER_DECELERATION * deltaTime);
		}
		else if (this->velocity.x < 0.f)
		{
			this->velocity.x = std::min(0.f, this->velocity.x + PLAYER_DECELERATION * deltaTime);
		}
	}

	// vertical movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->onGround)
	{
		this->velocity.y = -PLAYER_JUMP_STRENGHT;
		this->onGround = false;
	}

	if (!this->onGround) this->velocity.y += GRAVITY * deltaTime;
	else this->velocity.y = 0.f;

	this->velocity.x += acceleration * deltaTime;
	adjustBetween(this->velocity.x, -PLAYER_MAX_SPEED, PLAYER_MAX_SPEED);
	this->hitbox.move(this->velocity * deltaTime);
}

void Player::updateAnimation(float deltaTime)
{
	this->playerState = PlayerState::IDLE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->playerState = PlayerState::WALK;
		this->flipped = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->playerState = PlayerState::WALK;
		this->flipped = false;
	}
	if (this->velocity.y != 0.f)
	{
		this->playerState = PlayerState::JUMP;
	}

	for (auto& a : animation) a->update(deltaTime, this->flipped);
}

void Player::render(sf::RenderTarget& target)
{
	//target.draw(this->hitbox);
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
}
