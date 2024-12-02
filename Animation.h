#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
private:
	sf::Sprite sprite;
	sf::IntRect currentFrame;

	int frameIndex;
	int totalFrames;
	float frameDuration;
	float frameTimer;

	sf::Vector2i frameSize;

public:
	Animation(const sf::Texture& texture, int totalFrames, float frameDuration, sf::Vector2i frameSize);
	virtual ~Animation();

	void setPosition(sf::Vector2f position);
	void setOrigin(sf::Vector2f origin);
	void setScale(sf::Vector2f scale);
	void setSize(sf::Vector2f size);
	void setTransparency(int alpha);

	int getTransparency() const;

	void update(float deltaTime, bool flipped);
	void render(sf::RenderTarget& target, sf::Vector2f position);
};

