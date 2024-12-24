#include "AirSneakers.h"
#include "Player.h"

AirSneakers::AirSneakers(Player* player) :
	PowerUp(player)
{
	this->type = PowerUpType::AIR_SNEAKERS;
	this->duration = this->durationMax = AIR_SNEAKERS_DURATION;
	this->icon.setTexture(Resources::textures["AIR_SNEAKERS"]);
	this->animations.push_back(new Animation(Resources::textures["AIR_SNEAKERS_EFFECT"], 6, 0.1f, sf::Vector2i(120, 116)));
	this->animations[0]->setCenter();

	this->player->setJumpTimerMax(SNEAKERS_JUMP_TIMER);
}

AirSneakers::~AirSneakers()
{
	this->player->setJumpTimerMax(PLAYER_JUMP_TIME);
}

void AirSneakers::applyPowerUp(float deltaTime)
{
}
