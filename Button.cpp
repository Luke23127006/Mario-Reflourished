#include "Button.h"








Button::Button()
{
	// button size
	buttonSize = sf::Vector2f(200, 50);
	button.setSize(buttonSize);
	// button color
	buttonColor = PINK;
	buttonColorHover = lightenColor(buttonColor, 100);
	button.setFillColor(buttonColor);
	// outline color
	button.setOutlineThickness(3.0);
	outlineColor = sf::Color::Magenta;
	outlineColorHover = sf::Color::Green;
	button.setOutlineColor(outlineColor);

	
	

	isHovered = false;
	
}


Button::~Button()
{
	for (Command* command : commands)
	{
		delete command;
	}
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
	updateSizeButton();
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
	sf::Vector2f minSize = sf::Vector2f(200, 50);
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


// For command

void Button::addCommand(Command *command)
{
	std::cout << "Add command\n";
	if (command == nullptr) return;
	commands.push_back(command);
}

void Button::click()
{
	for (Command* command : commands)
	{
		command->execute();
	}
}

Command* Button::getCommand(int index)
{
	if (index < 0 || index >= commands.size()) return nullptr;
	return commands[index];
}



sf::Vector2f Button::getPosition()
{
	return button.getPosition();
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

bool Button::isHoverMouse()
{
	
	if (button.getGlobalBounds().contains(MOUSE_VIEW_POSITION))
	{
		if (MOUSE_POSITION.x < 0 || MOUSE_POSITION.x > WINDOW_SIZE.x
			|| MOUSE_POSITION.y < 0 || MOUSE_POSITION.y > WINDOW_SIZE.y)
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
void Button::colorHoverButton()
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