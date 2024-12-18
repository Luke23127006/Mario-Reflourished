#include "Shield.h"
#include "Player.h"

Shield::Shield(Player* player) :
	PowerUp(player)
{
	this->type = PowerUpType::SHIELD;
	this->duration = SHIELD_DURATION;
	this->player = player;
	
	this->player->health = 2;
}

Shield::~Shield()
{
	this->player->health = std::min(this->player->health, 1);
}

void Shield::applyPowerUp()
{
	if (this->player->health == 1) this->duration = 0.f;
}
