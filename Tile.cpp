#include "Tile.h"

Tile::Tile(sf::Vector2f position) :
	Object(sf::Vector2f(TILE_SIZE, TILE_SIZE), position),
	canShake(false)
{
}

Tile::Tile(sf::Vector2f position, sf::Texture& texture) : 
	Object(sf::Vector2f(50, 50), position),
	canShake(false)
{
	this->sprite.setTexture(texture);
	this->hitbox.setFillColor(sf::Color::Green);
	this->sprite.setScale(this->hitbox.getSize().x / texture.getSize().x, this->hitbox.getSize().y / texture.getSize().y);
}

Tile::Tile(sf::Vector2f position, sf::Texture& texture, bool canShake) :
	Object(sf::Vector2f(50, 50), position),
	canShake(canShake)
{
	this->sprite.setTexture(texture);
	this->hitbox.setFillColor(sf::Color::Green);
	this->sprite.setScale(this->hitbox.getSize().x / texture.getSize().x, this->hitbox.getSize().y / texture.getSize().y);
}

Tile::Tile(sf::Vector2f position, sf::Texture& texture, bool canShake, bool breakable) :
	Object(sf::Vector2f(50, 50), position),
	canShake(canShake),
	breakable(breakable)
{
	this->sprite.setTexture(texture);
	this->hitbox.setFillColor(sf::Color::Green);
	this->sprite.setScale(this->hitbox.getSize().x / texture.getSize().x, this->hitbox.getSize().y / texture.getSize().y);
}

Tile::~Tile()
{
	while (!particles.empty())
	{
		delete particles.back();
		particles.pop_back();
	}
}

const bool Tile::isHarming() const
{
	return this->harming;
}

const bool Tile::isShaking() const
{
	return this->shakeDuration > 0.f;
}

const bool Tile::isDanger() const
{
	return this->danger;
}

const bool Tile::isSolid() const
{
	return this->solid;
}

const bool Tile::isBreakable() const
{
	return this->breakable;
}

const bool Tile::isBroken() const
{
	return this->breakDuration <= 0.f;
}

const bool Tile::isNeedUpdating() const
{
	return this->shakeDuration > 0.f || (this->breakDuration > 0.f && this->breakDuration <= TILE_BREAK_DURATION);
}

void Tile::seftBreak()
{
	this->breakDuration = TILE_BREAK_DURATION;
	this->solid = false;
	this->enabled = false;

	float width = this->hitbox.getSize().x;
	float height = this->hitbox.getSize().y;

	particles.push_back(new Particle(*this->sprite.getTexture(), this->getPosition(), sf::Vector2f(-200.f, -800.f), sf::Vector2f(0.f, GRAVITY), 1.f));
	particles.back()->setTextureRect(sf::IntRect(0, 0, width / 2, height / 2));
	particles.push_back(new Particle(*this->sprite.getTexture(), this->getPosition() + sf::Vector2f(width / 2,  0.f), sf::Vector2f(200.f, -800.f), sf::Vector2f(0.f, GRAVITY), 1.f));
	particles.back()->setTextureRect(sf::IntRect(width / 2, 0, width / 2, height / 2));
	particles.push_back(new Particle(*this->sprite.getTexture(), this->getPosition() + sf::Vector2f(0.f, height / 2), sf::Vector2f(-200.f, -400.f), sf::Vector2f(0.f, GRAVITY), 1.f));
	particles.back()->setTextureRect(sf::IntRect(0, height / 2, width / 2, height / 2));
	particles.push_back(new Particle(*this->sprite.getTexture(), this->getPosition() + sf::Vector2f(width / 2, height / 2), sf::Vector2f(200.f, -400.f), sf::Vector2f(0.f, GRAVITY), 1.f));
	particles.back()->setTextureRect(sf::IntRect(width / 2, height / 2, width / 2, height / 2));
	Resources::sounds["MARIO_BREAK_BLOCK"].play();
}

void Tile::stopHarming()
{
	this->harming = false;
}

void Tile::shake()
{
	if (!this->canShake) return;
	this->shakeDuration = TILE_SHAKE_DURATION;
	this->harming = true;
}

void Tile::update(float deltaTime)
{
	if (this->breakDuration > 0.f)
	{
		this->breakDuration = std::max(0.f, this->breakDuration - deltaTime);
		for (auto& p : particles) p->update(deltaTime);
		return;
	}
	this->shakeDuration = std::max(0.f, this->shakeDuration - deltaTime);
	this->harming = false;

	if (this->shakeDuration > 0.f)
	{
		float shakeStrength = 1000.f;
		this->sprite.setPosition(
			this->getPosition() + shakeStrength * sf::Vector2f(0.f, this->shakeDuration * this->shakeDuration - TILE_SHAKE_DURATION * this->shakeDuration));
	}
	else
	{
		this->sprite.setPosition(this->getPosition());
	}
}

void Tile::render(sf::RenderTarget& target)
{
	//target.draw(this->hitbox);
	if (this->breakDuration == -1.f) target.draw(this->sprite);
	else if (this->breakDuration > 0.f)
	{
		for (auto& p : particles) p->render(target);
	}
}
