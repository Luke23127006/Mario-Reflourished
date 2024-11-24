#pragma once
#include <SFML\Graphics.hpp>
#include<string>
#include "Button.h"
#include<vector>
#include "UserInterface.h"
#include "Animation.h"
#include <fstream>
#include<direct.h>
class Login : public Scene {
private:
	sf::Texture loginTexture;
	Text errorLogin;
	Text errorRegister;
	Animation* loginAnimation;
	Button userNameButton;
	Text hiddenUserName;
	Button passwordButton;
	Text hiddenPassWord;
	Button confirmPassWordButton;
	Text hiddenConfirm;
	Button registerButton;
	Button backButton;
	std::vector<Text*> hiddenTexts;
	bool isPressedEnter;
	bool goToPlayScene;
	bool backToWelcome;
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
	void updateHoverButton(sf::RenderWindow& window) override;
	void updateClickButton(sf::RenderWindow& window, bool& held);
	void updateRegisterMovement(float dt);
	void updateText();
	void addConfirmButton();
	void resetAfterRegister();
	void updateBackgroundAnimation(float dt);
	void draw(sf::RenderWindow& window) override;
	void update(float dt) override;
	void render(sf::RenderWindow& window, bool& held) override;
	GameState getNextScene() override;
	bool checkAccount();
	bool checkRegister();
	~Login();
};
