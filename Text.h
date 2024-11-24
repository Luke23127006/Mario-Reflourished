#pragma once

#include "Resources.h"

#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>

class Text {
private:

	sf::Text buttonText;
	sf::Font font;
	sf::Color textColor;
	std::string text;
	float textSize;
	sf::Vector2f position;
	bool isAbleToWrite;
	bool isShiftPressed;
	bool isBackspacePressed;
	bool isEnterPressed;
	bool keyStates[256];
public:
	Text();
	void setPosition(sf::Vector2f position);
	void setTextColor(sf::Color color);
	void setText(std::string text);
	void setTextSize(float size);
	void setFont(sf::Font font);
	int getTextSize();
	std::string getText();
	void draw(sf::RenderWindow& window);
	sf::FloatRect getGlobalBounds();
	sf::FloatRect getLocalBounds();
	void updateText();
	void updateSize();
	void setAbleToWrite(bool ableToWrite);
	void updateShift();
	void updateBackspace();
	void updateEnter();
	void move(const sf::Vector2f vector);
};