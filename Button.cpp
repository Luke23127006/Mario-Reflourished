#include "Button.h"








Button::Button()
{
	/*if (!font.loadFromFile("Mario.ttf"))
	{
		std::cerr << "Cannot load default font !\n";
	}*/
	font = Resources::fonts["Standard"];
	buttonSize = sf::Vector2f(200, 50);
	button.setSize(buttonSize);
	// buttonColor
	buttonColor = sf::Color::Transparent;
	buttonColorHover = lightenColor(buttonColor, 100);
	button.setFillColor(buttonColor);
	// button outline
	button.setOutlineThickness(1.7);
	outlineColor = sf::Color::Magenta;
	/*outlineColorHover = lightenColor(outlineColor, 138);*/
	outlineColorHover = sf::Color::Green;
	button.setOutlineColor(outlineColor);
	// button text
	
	buttonText.setFont(font);
	textSize = 25;
	buttonText.setCharacterSize(textSize);
	buttonText.setFillColor(sf::Color::Green);
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
	textColor = color;
	buttonText.setFillColor(textColor);
}

void Button::setText(std::string text)
{
	buttonText.setString(text);
}

void Button::setTextSize(float size)
{
	textSize = size;
	buttonText.setCharacterSize(textSize);
}

void Button::setFont(sf::Font font)
{
	buttonText.setFont(font);
}

sf::Vector2f Button::getSize()
{
	return buttonSize;
}
void Button::draw(sf::RenderWindow& window)
{
	window.draw(button);
	window.draw(buttonText);
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

