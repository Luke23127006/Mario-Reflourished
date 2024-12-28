#include "VICTORYBlock.h"








VICTORYBlock::VICTORYBlock(sf::Vector2f position) :
	Tile(position)
{


	this->sprite.setTexture(Resources::textures["VICTORY"]);
	this->sprite.setOrigin(-25, -25);
	this->sprite.setScale(100.f / 2500, 100.f / 2500);
	this->sprite.setPosition(sf::Vector2f(this->getPosition().x - 25, this->getPosition().y - 25));
	
}

VICTORYBlock::~VICTORYBlock()
{
	
}



