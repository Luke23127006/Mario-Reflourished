#include "Magnet.h"
#include "Player.h"

Magnet::Magnet(Player* player) :
	PowerUp(player)
{
	this->type = PowerUpType::MAGNET;
	this->duration = this->durationMax = MAGNET_DURATION;
	this->icon.setTexture(Resources::textures["MAGNET"]);
	this->animations.push_back(new Animation(Resources::textures["MAGNET_EFFECT"], 5, 0.1f, sf::Vector2i(96, 96)));
	this->animations[0]->setCenter();
	this->animations[0]->setTransparency(128);
}

Magnet::~Magnet()
{
}

void Magnet::applyPowerUp(float deltaTime)
{
	std::vector<Coin*>& coins = this->player->getCoins();

	sf::Vector2f playerCenter(this->player->getGlobalBounds().left + this->player->getGlobalBounds().width / 2, 
								this->player->getGlobalBounds().top + this->player->getGlobalBounds().height / 2);
	for (auto& coin : coins)
	{
		sf::Vector2f coinCenter(coin->getGlobalBounds().left + coin->getGlobalBounds().width / 2,
			coin->getGlobalBounds().top + coin->getGlobalBounds().height / 2);

		sf::Vector2f direction = playerCenter - coinCenter;
		float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

		if (distance < MAGNET_RADIUS)
		{
			float speedFactor;
			speedFactor = MAGNET_RADIUS * MAGNET_RADIUS / distance - MAGNET_RADIUS;
			speedFactor = std::min(speedFactor, COIN_MAX_SPEED);

			direction /= abs(playerCenter.x - coinCenter.x);
			coin->move(direction * speedFactor, deltaTime);
		}
	}
}
