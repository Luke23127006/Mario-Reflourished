#pragma once
#include<iostream>
#include<string>
#include<SFML\Graphics.hpp>
#include "Resources.h"




class Button
{
private:
	sf::RectangleShape button;
	sf::Color outlineColor;
	sf::Color outlineColorHover;
	sf::Text buttonText;
	sf::Vector2f buttonSize;
	float textSize;
	bool isHovered;
	sf::Color buttonColor;
	sf::Color buttonColorHover;
	sf::Color textColor;
	std::string text;
	sf::Font font;
	sf::Color colorHover;

public:
	Button();
	void setPosition(sf::Vector2f position);
	void setButtonSize(sf::Vector2f size);
	void setButtonColor(sf::Color color);
	void setTextColor(sf::Color color);
	void setText(std::string text);
	void setTextSize(float size);
	void setFont(sf::Font font);
	sf::Vector2f getSize();
	void draw(sf::RenderWindow& window);
	bool isHoverMouse(sf::RenderWindow& window);
	sf::Color lightenColor(const sf::Color& color, int increase);
	void colorHoverButton(sf::RenderWindow& window);
	void changeHovered();
};
