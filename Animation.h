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

	float flipTimer = 0.0f;
	float flipInterval = 0.1f;
	sf::Vector2i frameSize;

public:
	Animation(const sf::Texture& texture, int totalFrames, float frameDuration, sf::Vector2i frameSize);
	virtual ~Animation();

	const sf::Vector2f getSize() const;

	void setRotation(float angle);
	void setPosition(sf::Vector2f position);
	void setOrigin(sf::Vector2f origin);
	void setScale(sf::Vector2f scale);
	void setSize(sf::Vector2f size);
	void setTransparency(int alpha);
	void setCenter();

	void update(float deltaTime, bool flipped);
	void render(sf::RenderTarget& target, sf::Vector2f position);
};

