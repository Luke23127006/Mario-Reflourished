#pragma once

#include "Global.h"
#include "Resources.h"
#include "Text.h"

#include<iostream>
#include<string>
#include<SFML\Graphics.hpp>
#include "CommandList.h"

class Button
{
private:
	sf::RectangleShape button;
	sf::Vector2f buttonSize;
	// outline
	sf::Color outlineColor;
	sf::Color outlineColorHover;
	
	// hover
	bool isHovered;
	sf::Color buttonColor;
	sf::Color buttonColorHover;

	// text
	Text buttonText;


	
	// command
	std::vector<Command*> commands;
	
public:
	Button();
	//Button(std::string text, sf::Vector2f position);
	~Button();
	void setPosition(sf::Vector2f position);
	void setButtonSize(sf::Vector2f size);
	void setButtonColor(sf::Color color);
	void setTextColor(sf::Color color);
	void setText(std::string text);
	void setFont(sf::Font font);

	// for command
	void addCommand(Command *command);
	Command* getCommand(int index);
	void click();
	
	// for input text
	int getTextSize();
	std::string getText();
	void updateSizeButton();

	


	// for render
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	void draw(sf::RenderWindow& window);

	// for hover
	bool isHoverMouse();
	sf::Color lightenColor(const sf::Color& color, int increase);
	void colorHoverButton();
	void changeHovered();
	void move(const sf::Vector2f vector);


};
