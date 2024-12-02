#pragma once

#include "Animation.h"

#include "Scene.h"

#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <direct.h>

class Login : public Scene {
private:
	sf::Texture loginTexture;
	Text errorLogin;
	Text errorRegister;
	Animation* loginAnimation;
	// User name button
	Button* userNameButton;
	Text hiddenUserName;

	// Password button
	Button* passwordButton;
	Text hiddenPassWord;

	// Confirm password button
	Button* confirmPassWordButton;
	Text hiddenConfirm;

	// Register button
	Button* registerButton;

	// Back button
	Button* backButton;

	std::vector<Text*> hiddenTexts;

	bool isRegister;
	bool updateRegisterAnimation;
	float moveTime;
	float speedRegister;
	float speedconfirmPassWord;
	bool isErrorLogin;
	bool isErrorRegister;
	
public :
	Login(sf::RenderTexture& window);
	void loadTexture();
	void updateHoverButton() override;
	void updateClickButton(bool& held) override;
	void updateRegisterMovement(float dt);
	//void updateText();
	void addConfirmButton();
	void resetAfterRegister();
	void updateBackgroundAnimation(float dt);
	void draw(sf::RenderWindow& window) override;
	void update(float dt, bool& held) override;
	void render(sf::RenderWindow& window) override;
	GameState getNextScene() override;
	bool checkAccount();
	bool checkRegister();
	~Login();
};
