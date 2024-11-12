#include "Animation.h"

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

void Animation::update(float deltaTime, bool flipped)
{
	this->frameTimer = std::max(0.f, this->frameTimer - deltaTime);

	if (this->frameTimer == 0)
	{
		this->frameTimer = this->frameDuration;

		this->frameIndex = (this->frameIndex + 1) % this->totalFrames;
		this->currentFrame.left = this->frameIndex * this->frameSize.x;
		if (flipped) this->currentFrame.left = -this->currentFrame.left;
	}

	this->sprite.setTextureRect(this->currentFrame);
}

void Animation::render(sf::RenderTarget& target, sf::Vector2f position)
{
	this->sprite.setPosition(position);
	target.draw(this->sprite);
}
