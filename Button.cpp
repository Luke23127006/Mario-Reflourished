#include "Button.h"








Button::Button()
{

	//font = Resources::fonts["Standard"];
	buttonSize = sf::Vector2f(200, 50);
	button.setSize(buttonSize);
	// buttonColor
	buttonColor = PINK;
	buttonColorHover = lightenColor(buttonColor, 100);
	button.setFillColor(buttonColor);
	// button outline
	button.setOutlineThickness(1.7);
	outlineColor = sf::Color::Magenta;
	outlineColorHover = sf::Color::Green;
	button.setOutlineColor(outlineColor);
	// button text
	
	
	colorHover = sf::Color::Green;

	isHovered = false;
	
}

void Button::setPosition(sf::Vector2f position)
{
	sf::Vector2f actualPosition = position - buttonSize / 2.0f;
	button.setPosition(actualPosition);
	
	sf::FloatRect textBounds = buttonText.getLocalBounds();

	
	sf::Vector2f textPositionOffset(
		(buttonSize.x - textBounds.width) / 2.0f - textBounds.left,
		(buttonSize.y - textBounds.height) / 2.0f - textBounds.top
	);

	
	buttonText.setPosition(actualPosition + textPositionOffset);
	
}


void Button::setButtonSize(sf::Vector2f size)
{
	buttonSize = size;
	button.setSize(buttonSize);
}

void Button::setButtonColor(sf::Color color)
{
	buttonColor = color;
	buttonColorHover = lightenColor(buttonColor, 100);
	button.setFillColor(buttonColor);
}

void Button::setTextColor(sf::Color color)
{
	buttonText.setTextColor(color);
}

void Button::setText(std::string text)
{
	buttonText.setText(text);
}
std::string Button::getText()
{
	return buttonText.getText();
}
int Button::getTextSize()
{
	return buttonText.getTextSize();
}
void Button::updateSizeButton()
{
	sf::Vector2f previousSize = buttonSize;
	if (buttonSize.x <= buttonText.getGlobalBounds().width)
	{
		buttonSize.x = buttonText.getGlobalBounds().width + 20;
		button.setSize(buttonSize);
	}

	this->setPosition(button.getPosition() + previousSize / 2.0f);
}



void Button::setFont(sf::Font font)
{
	buttonText.setFont(font);
}

void Button::setAbleToWrite(bool ableToWrite)
{
	isAbleToWrite = ableToWrite;
	buttonText.setAbleToWrite(ableToWrite);
}


sf::Vector2f Button::getPosition()
{
	return button.getPosition();
}
void Button::updateText()
{
	if (!isAbleToWrite) return;
	float oldTextSize = buttonText.getGlobalBounds().width;
	buttonText.updateText();
	float newTextSize = buttonText.getGlobalBounds().width;
	float offset = (newTextSize - oldTextSize);
	float min = std::max(200.0f, button.getSize().x + offset);
	/*button.setSize(sf::Vector2f(min, buttonSize.y)); 
	button.setPosition(button.getPosition() - sf::Vector2f(offset / 2.0f, 0));*/
	this->setButtonSize(sf::Vector2f(min, buttonSize.y));
	this->setPosition(button.getPosition() - sf::Vector2f(offset / 2.0f, 0) + button.getSize() / 2.0f);
}
sf::Vector2f Button::getSize()
{
	return buttonSize;
}
void Button::draw(sf::RenderWindow& window)
{
	window.draw(button);
	buttonText.draw(window);
}
sf::Color Button::lightenColor(const sf::Color& color, int increase) {
	int r = std::min(color.r + increase, 255);  // Tăng giá trị đỏ
	int g = std::min(color.g + increase, 255);  // Tăng giá trị xanh lá
	int b = std::min(color.b + increase, 255);  // Tăng giá trị xanh dương
	return sf::Color(r, g, b, color.a);         // Giữ nguyên độ trong suốt
}

bool Button::isHoverMouse(sf::RenderWindow& window)
{
	sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(window));

	sf::Vector2f mousePositionView = window.mapPixelToCoords(mousePosition);
	if (button.getGlobalBounds().contains(mousePositionView))
	{
		if (mousePosition.x < 0 || mousePosition.x > window.getSize().x
			|| mousePosition.y < 0 || mousePosition.y > window.getSize().y)
		{
			return false;
		}
		isHovered = true;
		return true;
	}

	return false;
}

void Button::changeHovered()
{
	isHovered = !isHovered;

}
void Button::colorHoverButton(sf::RenderWindow& window)
{
	if (isHovered)
	{
		button.setFillColor(buttonColorHover);
		button.setOutlineColor(outlineColorHover);
	}
	else
	{
		button.setFillColor(buttonColor);
		button.setOutlineColor(outlineColor);
	}
}

void Button::move(const sf::Vector2f vector)
{
	button.move(vector);
	buttonText.move(vector);
}