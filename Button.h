#pragma once
#include<iostream>
#include<string>
#include<SFML\Graphics.hpp>
#include "Resources.h"
#include "Text.h"
#include "Global.h"


class Button
{
private:
	sf::RectangleShape button;
	sf::Color outlineColor;
	sf::Color outlineColorHover;
	
	sf::Vector2f buttonSize;
	float textSize;
	bool isHovered;
	sf::Color buttonColor;
	sf::Color buttonColorHover;
	Text buttonText;
	sf::Color colorHover;
	bool isAbleToWrite;
	
public:
	Button();
	void setPosition(sf::Vector2f position);
	void setButtonSize(sf::Vector2f size);
	void setButtonColor(sf::Color color);
	void setTextColor(sf::Color color);
	void setText(std::string text);
	int getTextSize();
	std::string getText();
	void updateSizeButton();
	void setFont(sf::Font font);
	void setAbleToWrite(bool ableToWrite);
	sf::Vector2f getPosition();
	void updateText();
	sf::Vector2f getSize();
	void draw(sf::RenderWindow& window);
	bool isHoverMouse(sf::RenderWindow& window);
	sf::Color lightenColor(const sf::Color& color, int increase);
	void colorHoverButton(sf::RenderWindow& window);
	void changeHovered();
	void move(const sf::Vector2f vector);


};
