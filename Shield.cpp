#include "Shield.h"
#include "Player.h"

Shield::Shield(Player* player) :
	PowerUp(player)
{
	this->type = PowerUpType::SHIELD;
	this->duration = this->durationMax = SHIELD_DURATION;
	this->icon.setTexture(Resources::textures["SHIELD"]);
	this->player = player;
	
	this->player->setHealth(2);
}

Shield::~Shield()
{
	this->player->setHealth(1);
}

void Shield::applyPowerUp(float deltaTime)
{
	if (this->player->getHealth() == 1) this->duration = 0.f;
}
