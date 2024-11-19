#pragma once
#include "Login.h"







Login::Login(sf::RenderTexture& window)
{
	// Handle Error Messages
	errorLogin.setText("User Name or Password is incorrect");
	errorLogin.setTextColor(sf::Color::Red);
	errorRegister.setText("User Name is already exist or confirmPassword isnot correct");
	errorRegister.setTextColor(sf::Color::Red);
	errorLogin.setPosition(sf::Vector2f(window.getSize().x / 2 - errorLogin.getGlobalBounds().getSize().x / 2, window.getSize().y / 2 - userNameButton.getSize().y * 2- errorLogin.getGlobalBounds().getSize().y));
	errorRegister.setPosition(sf::Vector2f(window.getSize().x / 2 - errorRegister.getGlobalBounds().getSize().x / 2, window.getSize().y / 2 - userNameButton.getSize().y * 2 - errorRegister.getGlobalBounds().getSize().y));
	// Hidden Text
	hiddenTexts.push_back(&hiddenUserName);
	hiddenTexts.push_back(&hiddenPassWord);
	hiddenTexts.push_back(&hiddenConfirm);

	// All Buttons
	buttons.push_back(&userNameButton);
	buttons.push_back(&passwordButton);
	//buttons.push_back(&confirmPassWordButton);
	buttons.push_back(&registerButton);
	buttons.push_back(&backButton);

	// user name
	hiddenUserName.setText("User Name");
	userNameButton.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - userNameButton.getSize().y));
	sf::Vector2f offSet = (userNameButton.getSize() - hiddenUserName.getGlobalBounds().getSize()) / 2.0f;
	hiddenUserName.setPosition(userNameButton.getPosition() + offSet);
	userNameButton.setAbleToWrite(false);
		
	// password
	hiddenPassWord.setText("Password");
	passwordButton.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + passwordButton.getSize().y));
	offSet = (passwordButton.getSize() - hiddenPassWord.getGlobalBounds().getSize()) / 2.0f;
	hiddenPassWord.setPosition(passwordButton.getPosition() + offSet);
	passwordButton.setAbleToWrite(false);

	// confirm password
	hiddenConfirm.setText("Confirm Pass");
	confirmPassWordButton.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + confirmPassWordButton.getSize().y));
	offSet = (confirmPassWordButton.getSize() - hiddenConfirm.getGlobalBounds().getSize()) / 2.0f;
	hiddenConfirm.setPosition(confirmPassWordButton.getPosition() + offSet);
	passwordButton.setAbleToWrite(false);

	// register
	registerButton.setText("Register");
	registerButton.setPosition(sf::Vector2f(window.getSize().x - registerButton.getSize().x / 2, window.getSize().y - registerButton.getSize().y / 2));
	registerButton.setAbleToWrite(false);

	// back
	backButton.setText("Back");
	backButton.setPosition(sf::Vector2f(window.getSize().x - backButton.getSize().x / 2 , backButton.getSize().y / 2));
	backButton.setAbleToWrite(false);

	// background
	loadTexture();
	loginAnimation->setPosition(sf::Vector2f(0, 0));
	loginAnimation->setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	selectedButton = -1;
	isPressedUp = false;
	isPressedDown = false;
	isPressedEnter = false;
	goToPlayScene = false;
	backToWelcome = false;
	isRegister = false;
	updateRegisterAnimation = false;
	isErrorLogin = false;
	isErrorRegister = false;
	moveTime = 0.5f;
	speedRegister = 0;
	speedconfirmPassWord = 0;
	std::cout << "Button size: " << buttons.size() << std::endl;
}


void Login::loadTexture()
{
	loginTexture = Resources::textures["Login Background"];
	int totalFrames = this->loginTexture.getSize().x / 240;
	loginAnimation = new Animation(loginTexture, totalFrames, 0.1f, sf::Vector2i(240, 135));
}


void Login::updateHoverButton(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{

		if (!isPressedDown)
		{
			if (selectedButton != -1)
				(*buttons[selectedButton]).changeHovered();
			selectedButton = (selectedButton + 1) % buttons.size();
			(*buttons[selectedButton]).changeHovered();
			isPressedDown = true;
			std::cout << "Down\n";
		}

	}
	else {
		isPressedDown = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{

		if (!isPressedUp)
		{
			if (selectedButton != -1)
				(*buttons[selectedButton]).changeHovered();
			else {
				selectedButton = static_cast<int>(buttons.size());
			}
			selectedButton = (selectedButton - 1 + buttons.size()) % static_cast<int>(buttons.size());
			(*buttons[selectedButton]).changeHovered();
			isPressedUp = true;
			std::cout << "Up\n";
		}

	}
	else {
		isPressedUp = false;
	}
	// Update Hover Mouse
	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i]->isHoverMouse(window))
		{
			if (i == selectedButton)
			{
				break;
			}
			if (selectedButton != -1)
				buttons[selectedButton]->changeHovered();
			selectedButton = i;
			buttons[i]->changeHovered();
		}
	}
	// Update Able to Write
	if (!isRegister)
	{
		for (int i = 0; i < 2; ++i)
		{
			if (i == selectedButton)
				buttons[i]->setAbleToWrite(true);
			else
				buttons[i]->setAbleToWrite(false);
		}
	}
	if (isRegister)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (i == selectedButton)
				buttons[i]->setAbleToWrite(true);
			else
				buttons[i]->setAbleToWrite(false);
		
		}
	}


	
}


void Login::updateClickButton(sf::RenderWindow& window, bool& held)
{

	if (selectedButton == -1)
		return;
	if (!isRegister)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (!isPressedEnter)
			{
				isPressedEnter = true;
				switch (selectedButton)
				{
				case 0:
					buttons[selectedButton]->changeHovered();
					selectedButton++;
					buttons[selectedButton]->changeHovered();
					break;
				case 1:
					// Handle PassWord
					if (checkAccount())
					{
						goToPlayScene = true;
					}
					else {
						isErrorLogin = true;
					}
					break;

				}
			}
			
		}
		else {
			isPressedEnter = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
			|| (sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttons[selectedButton]->isHoverMouse(window)))
		{
			switch (selectedButton)
			{
			case 2:
				isRegister = true;
				updateRegisterAnimation = true;
				speedRegister = (backButton.getPosition().y - registerButton.getPosition().y) / moveTime;
				speedconfirmPassWord = (2 * confirmPassWordButton.getSize().y) / moveTime;
				addConfirmButton();
				resetAfterRegister();
				break;
			case 3:
				backToWelcome = true;
				break;
			default:
				break;
			}
		}
	}

	if (isRegister)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (!isPressedEnter)
			{
				isPressedEnter = true;
				switch (selectedButton)
				{
				case 0:
					buttons[selectedButton]->changeHovered();
					selectedButton++;
					buttons[selectedButton]->changeHovered();
					break;
				case 1:
					buttons[selectedButton]->changeHovered();
					selectedButton++;
					buttons[selectedButton]->changeHovered();
					break;
				case 2:
					// Handle Confirm Password
					if (checkRegister())
					{
						goToPlayScene = true;
					}
					else {
						isErrorRegister = false;
					}
					break;
				}
			}
			
		}
		else {
			isPressedEnter = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
			|| (sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttons[selectedButton]->isHoverMouse(window)))
		{
			switch (selectedButton)
			{
			case 3:
				backToWelcome = true;
				break;
			}
		}
	}
}

void Login::updateText()
{

	if (selectedButton == -1) return;
	buttons[selectedButton]->updateText();

}

void Login::updateBackgroundAnimation(float dt)
{
	loginAnimation->update(dt, false);
}

void Login::draw(sf::RenderWindow& window)
{
	loginAnimation->render(window, sf::Vector2f(0, 0));
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->draw(window);
		
	}
	for (int i = 0; i < hiddenTexts.size(); i++)
	{
		if (buttons[i]->getTextSize() != 0) continue;
		hiddenTexts[i]->draw(window);
	}
	if (isErrorLogin)
	{
		errorLogin.draw(window);
	}
	if (isErrorRegister)
	{
		errorRegister.draw(window);
	}
	
}

void Login::updateRegisterMovement(float dt)
{
	if (!updateRegisterAnimation) {
		return;
	}
	if (moveTime <= 0)
	{
		updateRegisterAnimation = false;
		selectedButton = -1;
		buttons.pop_back();
		return;
	}

	registerButton.move(sf::Vector2f(0, speedRegister * dt));
	confirmPassWordButton.move(sf::Vector2f(0, speedconfirmPassWord * dt));
	hiddenConfirm.move(sf::Vector2f(0, speedconfirmPassWord * dt));
	moveTime -= dt;

}

void Login::update(float dt)
{
	
	updateText();
	updateBackgroundAnimation(dt);
	updateRegisterMovement(dt);
}


void Login::render(sf::RenderWindow& window, bool& held)
{
	updateHoverButton(window);
	updateClickButton(window, held);
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->colorHoverButton(window);
	}
	draw(window);

}




void Login::addConfirmButton()
{
	if (!isRegister) return;
	registerButton.changeHovered();
	selectedButton = 4;
	buttons.insert(buttons.begin() + 2, &confirmPassWordButton);
	std::swap(*(buttons.end() - 1), *(buttons.end() - 2));



}

void Login::resetAfterRegister()
{
	if (!isRegister) return;
	isErrorLogin = false;
	isErrorRegister = false;
	userNameButton.setText("");
	passwordButton.setText("");
	confirmPassWordButton.setText("");
	sf::Vector2f centerUser = userNameButton.getPosition() + userNameButton.getSize() / 2.0f;
	userNameButton.setButtonSize(sf::Vector2f(200, 50));
	userNameButton.setPosition(centerUser);
	sf::Vector2f centerPassword = passwordButton.getPosition() + passwordButton.getSize() / 2.0f;
	passwordButton.setButtonSize(sf::Vector2f(200, 50));
	passwordButton.setPosition(centerPassword);
	confirmPassWordButton.setButtonSize(sf::Vector2f(200, 50));
}

GameState Login::getNextScene()
{
	if (goToPlayScene)
	{
		goToPlayScene = false;
		return GameState::PLAY;
	}
	if (backToWelcome)
	{
		backToWelcome = false;
		return GameState::WELCOME;
	}
	return GameState::LOGIN;
}

Login::~Login()
{
	delete loginAnimation;
}


bool Login::checkAccount()
{
	std::string userName = userNameButton.getText();
	std::string passWord = passwordButton.getText();
	std::ifstream fin("./Resources/UserAccount/" + userName + "/" + userName + ".txt");
	if (!fin.is_open())
	{
		fin.close();
		return false;
	}
	std::string pass;
	getline(fin, pass);
	std::cout << pass << std::endl;
	fin.close();
	if (pass != passWord)
	{
		return false;
	}
	return true;
}

bool Login::checkRegister()
{
	if (checkAccount()) return false;
	std::string userName = userNameButton.getText();
	std::string passWord = passwordButton.getText();
	std::string confirmPass = confirmPassWordButton.getText();
	if (passWord != confirmPass)
	{
		return false;
	}

	bool makeFile = _mkdir(("./Resources/UserAccount/" + userName).c_str());
	std::ofstream fout("./Resources/UserAccount/" + userName + "/" + userName + ".txt");
	fout << passWord << std::endl;
	fout.close();
	return true;
}