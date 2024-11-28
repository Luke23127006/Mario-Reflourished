#include "CommandList.h"
#include "Button.h"







// Scene Command
changeSceneCommand::changeSceneCommand(const GameState& currentState, const GameState& nextState)
{
	this->currentState = currentState;
	this->nextState = nextState;

}




GameState changeSceneCommand::getScene()
{
	return currentState;
}
void changeSceneCommand::execute()
{
	currentState = nextState;

}


changeSceneCommand::~changeSceneCommand()
{
}




// Text Command

writeTextCommand::writeTextCommand(Button* button)
{
	this->button = button;
	isAbleToWrite = false;
}

writeTextCommand::writeTextCommand(Button* button, Text text)
{
	this->button = button;
	this->text = text;
	isAbleToWrite = false;
}

void writeTextCommand::updateText()
{
	
	textString = button->getText();
	text.setText(textString);
	float oldTextSize = 0;
	// Calculate the size of the text
	oldTextSize = text.getGlobalBounds().width;
	text.updateText();
	button->setText(text.getText());
	float newTextSize = 0;
	newTextSize = text.getGlobalBounds().width;
	float offset = newTextSize - oldTextSize;
	// Update the size of the button
	float minButtonSize = std::max(200.0f, button->getSize().x + offset);
	button->setButtonSize(sf::Vector2f(minButtonSize, button->getSize().y));
	button->setPosition(button->getPosition() - sf::Vector2f(offset / 2.0f, 0) + button->getSize() / 2.0f);


}


void writeTextCommand::execute()
{
	this->text.setAbleToWrite(isAbleToWrite);
	if (!isAbleToWrite)
		return;
	updateText();
}

void writeTextCommand::setAbleToWrite(bool ableToWrite)
{
	isAbleToWrite = ableToWrite;
}

writeTextCommand::~writeTextCommand()
{
}

