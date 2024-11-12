#include "Player.h"

Player::Player(sf::Vector2f size, sf::Vector2f position) :
	Entity(size, position),
	playerState(PlayerState::IDLE),
	invicibleTimer(0.f),
	coins(0),
	lives(3)
{
	animation.resize(PlayerState::DIE + 1);
	animation[PlayerState::IDLE] = new Animation(Resources::textures["MARIO_IDLE"], 1, 1, sf::Vector2i(42, 48));
	animation[PlayerState::WALK] = new Animation(Resources::textures["MARIO_WALK"], 3, 0.1f, sf::Vector2i(54, 48));
	animation[PlayerState::JUMP] = new Animation(Resources::textures["MARIO_JUMP"], 1, 1, sf::Vector2i(60, 48));
	animation[PlayerState::DIE] = new Animation(Resources::textures["MARIO_DIE"], 1, 1, sf::Vector2i(42, 42));
}

Player::~Player()
{
	for (auto& a : this->animation)
		delete a;
}

void Player::update(float deltaTime)
{
	this->invicibleTimer = std::max(0.f, this->invicibleTimer - deltaTime);
}

void Player::render(sf::RenderTarget& target)
{
	switch (this->playerState)
	{
	case PlayerState::IDLE:
		this->animation[PlayerState::IDLE]->render(target, this->hitbox.getPosition());
		break;
	case PlayerState::WALK:
		this->animation[PlayerState::WALK]->render(target, this->hitbox.getPosition());
		break;
	case PlayerState::JUMP:
		this->animation[PlayerState::JUMP]->render(target, this->hitbox.getPosition());
		break;
	case PlayerState::DIE:
		this->animation[PlayerState::DIE]->render(target, this->hitbox.getPosition());
		break;
	}
}
