#include "AirSneakers.h"
#include "Player.h"

AirSneakers::AirSneakers(Player* player) :
	PowerUp(player)
{
	this->type = PowerUpType::AIR_SNEAKERS;
	this->duration = AIR_SNEAKERS_DURATION;

	this->player->setJumpTimerMax(SNEAKERS_JUMP_TIMER);
}

AirSneakers::~AirSneakers()
{
	this->player->setJumpTimerMax(PLAYER_JUMP_TIME);
}

void AirSneakers::applyPowerUp(float deltaTime)
{
}
