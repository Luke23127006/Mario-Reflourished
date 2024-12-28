#include "Mushroom.h"
#include "Player.h"

Mushroom::Mushroom(Player* player) :
	PowerUp(player)
{
	this->player = player;
	this->duration = this->durationMax = MUSHROOM_DURATION;
	this->type = PowerUpType::MUSHROOM;
	this->icon.setTexture(Resources::textures["SUPER_MUSHROOM"]);;
	if (this->player->hasPowerUp(this->type)) return;
	this->player->setSize(sf::Vector2f(PLAYER_BIGGER_WIDTH, PLAYER_BIGGER_HEIGHT));
	this->player->move(sf::Vector2f(-PLAYER_BIGGER_WIDTH + PLAYER_WIDTH, -PLAYER_BIGGER_HEIGHT + PLAYER_HEIGHT));
	this->player->setCanBreakBlocks(true);
	this->player->setIsBig(true);
	this->player->setHealth(2);
}

Mushroom::~Mushroom()
{
	this->player->setCanBreakBlocks(false);
	this->player->setIsBig(false);
	this->player->setSize(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
}

void Mushroom::applyPowerUp(float deltaTime)
{
	if (this->duration == -1)
	{
		this->player->setHealth(2);
		this->player->setIsBig(true);
		return;
	}
	if (this->player->getHealth() == 1)
	{
		this->duration = 0.f;
		this->player->setCanBreakBlocks(false);
		this->player->setIsBig(false);
		this->player->setSize(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
	}
}
