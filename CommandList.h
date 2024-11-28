#pragma once
#include "Command.h"
#include "Text.h"
#include "Global.h"

class Button;





class changeSceneCommand : public Command
{
private:
	GameState currentState;
	GameState nextState;

public:
	changeSceneCommand(const GameState& currentState,const GameState& nextState);
	GameState getScene();
	void execute() override;
	~changeSceneCommand();
};

class writeTextCommand : public Command
{
private:
	Button* button;
	Text text;
	std::string textString;
	bool isAbleToWrite;
public:
	writeTextCommand(Button* button);
	writeTextCommand(Button* button, Text text);
	void setAbleToWrite(bool ableToWrite);
	void updateText();
	void execute() override;
	~writeTextCommand();


};







