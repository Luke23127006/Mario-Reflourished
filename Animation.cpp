#include "Animation.h"
#include <iostream>

Animation::Animation(const sf::Texture& texture, int totalFrames, float frameDuration, sf::Vector2i frameSize) :
	currentFrame(0, 0, frameSize.x, frameSize.y),
	frameIndex(0),
	totalFrames(totalFrames),
	frameDuration(frameDuration),
	frameTimer(0.f),
	frameSize(frameSize)
{
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(this->currentFrame);
}


Animation::~Animation()
{
}

const sf::Vector2f Animation::getSize() const
{
	return sf::Vector2f(this->frameSize);
}

void Animation::setRotation(float angle)
{
	this->sprite.setRotation(angle);
}

void Animation::setPosition(sf::Vector2f position)
{
	this->sprite.setPosition(position);
}

void Animation::setOrigin(sf::Vector2f origin)
{
	this->sprite.setOrigin(origin);
}

void Animation::setScale(sf::Vector2f scale)
{
	this->sprite.setScale(scale);
}

void Animation::setSize(sf::Vector2f size)
{
	this->sprite.setScale(size.x / this->frameSize.x, size.y / this->frameSize.y);
}

void Animation::setTransparency(int alpha)
{
	sf::Color color = this->sprite.getColor();
	color.a = alpha;
	this->sprite.setColor(color);
}

void Animation::setCenter()
{
	this->sprite.setOrigin(this->frameSize.x / 2, this->frameSize.y / 2);
}

void Animation::update(float deltaTime, bool flipped)
{
	this->frameTimer = std::max(0.f, this->frameTimer - deltaTime);

	this->flipTimer += deltaTime;
	if (this->frameTimer <= 0.f)
	{
		this->frameTimer = this->frameDuration;
		this->frameIndex = (this->frameIndex + 1) % this->totalFrames;
	}

	if (this->flipTimer > this->flipInterval)
	{
		if (!flipped)
		{
			this->currentFrame = sf::IntRect(this->frameIndex * this->frameSize.x, 0.f, frameSize.x, frameSize.y);
		}
		else
		{
			this->currentFrame = sf::IntRect((this->frameIndex + 1) * this->frameSize.x, 0.f, -frameSize.x, frameSize.y);
		}
		this->flipTimer = 0.f;
	}
	

	this->sprite.setTextureRect(this->currentFrame);
}

void Animation::render(sf::RenderTarget& target, sf::Vector2f position)
{
	this->sprite.setPosition(position);
	target.draw(this->sprite);
}