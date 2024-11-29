#include "LuckyBlock.h"

LuckyBlock::LuckyBlock(sf::Vector2f position, LuckyBlockType type) :
	Tile(position),
	type(type),
	activated(false)
{
	this->sprite.setTexture(Resources::textures["EMPTY_BLOCK"]);
	this->animation = new Animation(Resources::textures["LUCKY_BLOCK"], 4, 0.2f, sf::Vector2i(50, 50));
	this->particle = nullptr;

	this->canShake = true;
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

const bool LuckyBlock::isActivated() const
{
	return this->activated;
}

const LuckyBlockType LuckyBlock::getType() const
{
	return this->type;
}

const bool LuckyBlock::isNeedUpdating() const
{
	return (!this->activated || this->shakeDuration >= 0.f);
}

void LuckyBlock::seftBreak()
{
}

void LuckyBlock::activate()
{
	if (this->activated) return;
	this->activated = true;

	if (this->type == LuckyBlockType::COIN)
	{
		this->type = LuckyBlockType::ACTIVATED;
		this->particle = new Particle(Resources::textures["EMPTY_BLOCK"], this->getCenter(), sf::Vector2f(0.f, -200.f), sf::Vector2f(0.f, 200.f), 0.25f);
	}
}

void LuckyBlock::shake()
{
	Tile::shake();
	this->canShake = false;
}

PowerUp* LuckyBlock::launchPowerUp()
{
	this->type = LuckyBlockType::ACTIVATED;
	return EntityFactory::createPowerUp(this->getGlobalBounds());
}

void LuckyBlock::update(float deltaTime)
{
	Tile::update(deltaTime);
	if (this->activated)
	{
		if (this->particle && this->particle->isExpired())
		{
			delete this->particle;
			this->particle = nullptr;
		}
		if (this->particle) this->particle->update(deltaTime);
	}
	else
	{
		this->animation->update(deltaTime, false);
	}
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