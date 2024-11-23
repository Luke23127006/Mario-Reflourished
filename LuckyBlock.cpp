#include "LuckyBlock.h"

LuckyBlock::LuckyBlock(sf::Vector2f position, LuckyBlockType type) :
	Tile(position),
	type(type),
	activated(false)
{
	this->sprite.setTexture(Resources::textures["EMPTY_BLOCK"]);
	this->animation = new Animation(Resources::textures["LUCKY_BLOCK"], 4, 0.2f, sf::Vector2i(50, 50));
	this->particle = nullptr;
}

LuckyBlock::LuckyBlock(sf::Vector2f position, LuckyBlockType type, PowerUpType powerUpType)
	: Tile(position),
	type(type),
	powerUpType(powerUpType),
	activated(false)
{
	this->sprite.setTexture(Resources::textures["EMPTY_BLOCK"]);
	this->animation = new Animation(Resources::textures["LUCKY_BLOCK"], 4, 0.2f, sf::Vector2i(50, 50));
	this->particle = nullptr;
}

LuckyBlock::~LuckyBlock()
{
	delete this->animation;
	if (this->particle != nullptr) delete this->particle;
}

const sf::Vector2f LuckyBlock::getCenter() const
{
	return sf::Vector2f(this->hitbox.getPosition().x + this->hitbox.getSize().x / 2, this->hitbox.getPosition().y + this->hitbox.getSize().y / 2);
}

void LuckyBlock::activate()
{
	if (this->activated) return;
	this->activated = true;
	this->particle = new Particle(Resources::textures["EMPTY_BLOCK"], this->getCenter(), sf::Vector2f(0.f, -200.f), sf::Vector2f(0.f, 0.f), 0.25f);
}

PowerUpType LuckyBlock::getPowerUpType()
{
	return PowerUpType();
}

void LuckyBlock::update(float deltaTime)
{
	if (this->activated)
	{
		if (this->particle && this->particle->isExpired())
		{
			delete this->particle;
			this->particle = nullptr;
		}
		if (this->particle) this->particle->update(deltaTime);
	}
	else this->animation->update(deltaTime, false);
}

void LuckyBlock::render(sf::RenderTarget& target)
{
	if (this->activated)
	{
		if (this->particle)
		{
			this->particle->render(target);
		}
		target.draw(this->sprite);
	}
	else this->animation->render(target, this->hitbox.getPosition());
}