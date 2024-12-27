#include "Shield.h"
#include "Player.h"

Shield::Shield(Player* player) :
	PowerUp(player)
{
	this->isBack = false;
	this->type = PowerUpType::SHIELD;
	this->duration = this->durationMax = SHIELD_DURATION;
	this->icon.setTexture(Resources::textures["SHIELD"]);
	this->animations.push_back(new Animation(Resources::textures["SHIELD_EFFECT"], 6, 0.2f, sf::Vector2i(80, 96)));
	this->animations[0]->setCenter();
	this->animations[0]->setTransparency(72);
	
	this->player->setHealth(2);
}

Shield::~Shield()
{
	this->player->setHealth(1);
}

void Shield::applyPowerUp(float deltaTime)
{
	if (this->duration == -1)
	{
		this->player->setHealth(2);
		return;
	}
	if (this->player->getHealth() == 1) this->duration = 0.f;
}
