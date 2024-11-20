#include "Text.h"








Text::Text()
{
	font = Resources::fonts["Standard"];
	textColor = sf::Color::White;
	buttonText.setFont(font);
	this->textSize = 30;
	buttonText.setCharacterSize(textSize);
	buttonText.setFillColor(textColor);
	this->isAbleToWrite = false;
	this->isShiftPressed = false;
	this->isBackspacePressed = false;
	this->isEnterPressed = false;
	for (auto x : keyStates)
	{
		x = false;
	}
}

void Text::setPosition(sf::Vector2f position)
{
	buttonText.setPosition(position);
}

void Text::setTextColor(sf::Color color)
{
	textColor = color;
	buttonText.setFillColor(textColor);
}

void Text::setText(std::string text)
{
	this->text = text;
	buttonText.setString(text);
}

void Text::setTextSize(float size)
{
	textSize = size;
	buttonText.setCharacterSize(textSize);
}

void Text::setFont(sf::Font font)
{
	this->font = font;
	buttonText.setFont(font);
}

int Text::getTextSize()
{
	return text.length();
}

std::string Text::getText()
{
	return text;
}
void Text::draw(sf::RenderWindow& window)
{
	window.draw(buttonText);
}

sf::FloatRect Text::getGlobalBounds()
{
	return buttonText.getGlobalBounds();
}

sf::FloatRect Text::getLocalBounds()
{
	return buttonText.getLocalBounds();
}
void Text::updateBackspace()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		if (!isBackspacePressed)
		{
			if (text.size() > 0)
				text.pop_back();
			isBackspacePressed = true;
		}
	}
	else
	{
		isBackspacePressed = false;
	}
}
void Text::updateEnter()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (!isEnterPressed)
		{
			isAbleToWrite = false;
			isEnterPressed = true;
		}
	}
	else
	{
		isEnterPressed = false;
	}
}
void Text::updateShift()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		isShiftPressed = true;
	}
	else
	{
		isShiftPressed = false;
	}
}


void Text::setAbleToWrite(bool ableToWrite)
{
	isAbleToWrite = ableToWrite;
}
void Text::updateText()
{
	if (!isAbleToWrite)
		return;
	updateBackspace();
	updateEnter();
	updateShift();

	// Handle letter keys
	for (int i = 0; i < 26; i++) {
		sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(i + sf::Keyboard::A); // A-Z
		if (sf::Keyboard::isKeyPressed(key) && !keyStates[key]) {
			keyStates[key] = true; 
			if (isShiftPressed) {
				text += static_cast<char>('A' + i); // Uppercase
			}
			else {
				text += static_cast<char>('a' + i); // Lowercase
			}
		}
		else if (!sf::Keyboard::isKeyPressed(key)) {
			keyStates[key] = false; // Reset state
		}
	}

	// Handle number keys
	for (int i = 0; i < 10; i++) {
		sf::Keyboard::Key keyMain = static_cast<sf::Keyboard::Key>(i + sf::Keyboard::Num0); // Phím số trên hàng chính
		sf::Keyboard::Key keyNumpad = static_cast<sf::Keyboard::Key>(i + sf::Keyboard::Numpad0); // Phím số trên NumPad

		// Number in main board
		if (sf::Keyboard::isKeyPressed(keyMain) && !keyStates[keyMain]) {
			keyStates[keyMain] = true;
			text += static_cast<char>('0' + i);
		}
		else if (!sf::Keyboard::isKeyPressed(keyMain)) {
			keyStates[keyMain] = false;
		}

		// Number in NumPad
		if (sf::Keyboard::isKeyPressed(keyNumpad) && !keyStates[keyNumpad]) {
			keyStates[keyNumpad] = true;
			text += static_cast<char>('0' + i);
		}
		else if (!sf::Keyboard::isKeyPressed(keyNumpad)) {
			keyStates[keyNumpad] = false;
		}
	}
	// Handle Space key
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !keyStates[sf::Keyboard::Space]) {
		keyStates[sf::Keyboard::Space] = true;
		text += ' '; 
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		keyStates[sf::Keyboard::Space] = false;
	}

	std::cout << "hmmm" << std::endl;
	updateSize();
}
void Text::updateSize()
{
	buttonText.setString(text);
}

void Text::move(const sf::Vector2f vector)
{
	buttonText.move(vector);
}