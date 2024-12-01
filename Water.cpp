#include "Water.h"

Water::Water(sf::Vector2f position, bool isSurface) :
	Tile(position, Resources::textures["WATER_BELOW"]),
	animation(nullptr)
{
	if (isSurface)
	{
		animation = new Animation(Resources::textures["WATER_SURFACE"], 50, 0.03f, sf::Vector2i(50, 50));
		animation->setTransparency(128);
	}
	this->sprite.setColor(sf::Color(255, 255, 255, 128));
	this->solid = false;
}

Water::~Water()
{
}

const bool Water::isNeedUpdating() const
{
	return true;
}

void Water::update(float deltaTime)
{
	if (this->animation)
	{
		this->animation->update(deltaTime, false);
	}
}

void Water::render(sf::RenderTarget& target)
{
	if (this->animation)
	{
		this->animation->render(target, this->hitbox.getPosition());
	}
	else
	{
		Tile::render(target);
	}
}
