#include "Mushroom.h"
#include "Player.h"

Mushroom::Mushroom(Player* player) :
	PowerUp(player)
{
	this->player = player;
	this->duration = MUSHROOM_DURATION;
	this->type = PowerUpType::MUSHROOM;

	if (this->player->hasPowerUp(this->type)) return;
	this->player->setSize(sf::Vector2f(PLAYER_BIGGER_WIDTH, PLAYER_BIGGER_HEIGHT));
	this->player->move(sf::Vector2f(-PLAYER_BIGGER_WIDTH + PLAYER_WIDTH, -PLAYER_BIGGER_HEIGHT + PLAYER_HEIGHT));
	this->player->setCanBreakBlocks(true);
}

Mushroom::~Mushroom()
{
	this->player->setCanBreakBlocks(false);
	this->player->setSize(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
}

void Mushroom::applyPowerUp(float deltaTime)
{
}
