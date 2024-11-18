#include "LuckyBlock.h"

LuckyBlock::LuckyBlock(sf::Vector2f position, LuckyBlockType type) :
	Tile(position),
	type(type),
	activated(false),
	animation(nullptr)
{
}

LuckyBlock::LuckyBlock(sf::Vector2f position, LuckyBlockType type, PowerUpType powerUpType)
	: Tile(position),
	type(type),
	powerUpType(powerUpType),
	activated(false),
	animation(nullptr)
{
}

LuckyBlock::~LuckyBlock()
{
}

void LuckyBlock::activate()
{
}

PowerUpType LuckyBlock::getPowerUpType()
{
	return PowerUpType();
}

void LuckyBlock::update(float deltaTime)
{
}

void LuckyBlock::render(sf::RenderTarget& target)
{
}
