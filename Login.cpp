#pragma once
#include "Login.h"







Login::Login(sf::RenderTexture& window)
{
	
	

	// user name
	this->userNameButton = new Button();
	this->hiddenUserName.setText("User Name");
	this->userNameButton->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - userNameButton->getSize().y));
	this->userNameButton->addCommand(new changeSceneCommand(GameState::LOGIN, GameState::LOGIN));
	this->userNameButton->addCommand(new writeTextCommand(userNameButton));
	// hidden user name
	sf::Vector2f offSet = (userNameButton->getSize() - hiddenUserName.getLocalBounds().getSize()) / 2.0f - hiddenUserName.getLocalBounds().getPosition();
	this->hiddenUserName.setPosition(userNameButton->getPosition() + offSet);

		
	// password
	this->passwordButton = new Button();
	this->hiddenPassWord.setText("Password");
	this->passwordButton->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + passwordButton->getSize().y));
	this->passwordButton->addCommand(new changeSceneCommand(GameState::LOGIN, GameState::PLAY));
	this->passwordButton->addCommand(new writeTextCommand(passwordButton));
	// hidden password
	offSet = (passwordButton->getSize() - hiddenPassWord.getLocalBounds().getSize()) / 2.0f - hiddenPassWord.getLocalBounds().getPosition();
	this->hiddenPassWord.setPosition(passwordButton->getPosition() + offSet);


	// confirm password
	this->confirmPassWordButton = new Button();
	this->hiddenConfirm.setText("Confirm Pass");
	this->confirmPassWordButton->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + confirmPassWordButton->getSize().y));
	this->confirmPassWordButton->addCommand(new changeSceneCommand(GameState::LOGIN, GameState::PLAY));
	this->confirmPassWordButton->addCommand(new writeTextCommand(confirmPassWordButton));
	// hidden confirm password
	offSet = (confirmPassWordButton->getSize() - hiddenConfirm.getLocalBounds().getSize()) / 2.0f - hiddenConfirm.getLocalBounds().getPosition();
	this->hiddenConfirm.setPosition(confirmPassWordButton->getPosition() + offSet);


	// register
	this->registerButton = new Button();
	this->registerButton->setText("Register");
	this->registerButton->setPosition(sf::Vector2f(window.getSize().x - registerButton->getSize().x / 2, window.getSize().y - registerButton->getSize().y / 2));
	this->registerButton->addCommand(new changeSceneCommand(GameState::LOGIN, GameState::LOGIN));

	// back
	this->backButton = new Button();
	this->backButton->setText("Back");
	this->backButton->setPosition(sf::Vector2f(window.getSize().x - backButton->getSize().x / 2 , backButton->getSize().y / 2));
	this->backButton->addCommand(new changeSceneCommand(GameState::LOGIN, GameState::WELCOME));


	// background
	loadTexture();
	this->loginAnimation->setPosition(sf::Vector2f(0, 0));
	this->loginAnimation->setSize(sf::Vector2f(window.getSize().x, window.getSize().y));



	// All Buttons
	this->buttons.push_back(userNameButton);
	this->buttons.push_back(passwordButton);
	this->buttons.push_back(registerButton);
	this->buttons.push_back(backButton);


	// Handle Error Messages
	this->errorLogin.setText("User Name or Password is incorrect");
	this->errorLogin.setTextColor(sf::Color::Red);
	this->errorRegister.setText("UserName   is existed      or      ConfirmPassword   is not correct");
	this->errorRegister.setTextColor(sf::Color::Red);
	this->errorLogin.setPosition(sf::Vector2f(window.getSize().x / 2 - errorLogin.getGlobalBounds().getSize().x / 2, window.getSize().y / 2 - userNameButton->getSize().y * 2 - errorLogin.getGlobalBounds().getSize().y));
	this->errorRegister.setPosition(sf::Vector2f(window.getSize().x / 2 - errorRegister.getGlobalBounds().getSize().x / 2, window.getSize().y / 2 - userNameButton->getSize().y * 2 - errorRegister.getGlobalBounds().getSize().y));
	// Hidden Text
	this->hiddenTexts.push_back(&hiddenUserName);
	this->hiddenTexts.push_back(&hiddenPassWord);
	this->hiddenTexts.push_back(&hiddenConfirm);





	this->isRegister = false;
	this->updateRegisterAnimation = false;
	this->isErrorLogin = false;
	this->isErrorRegister = false;
	this->moveTime = 0.45f;
	this->speedRegister = 0;
	this->speedconfirmPassWord = 0;
	std::cout << "Button size: " << buttons.size() << std::endl;
}


void Login::loadTexture()
{
	this->loginTexture = Resources::textures["Login Background"];
	int totalFrames = this->loginTexture.getSize().x / 240;
	this->loginAnimation = new Animation(loginTexture, totalFrames, 0.1f, sf::Vector2i(240, 135));
}


void Login::updateHoverButton()
{
	Scene::updateHoverButton();
	// Update Able to Write
	if (!this->isRegister)
	{
		for (int i = 0; i < 2; ++i)
		{
			if (i == this->selectedButton)
			{
				dynamic_cast<writeTextCommand*>(this->buttons[i]->getCommand(1))->setAbleToWrite(true);
			}
				
			else
				dynamic_cast<writeTextCommand*>(this->buttons[i]->getCommand(1))->setAbleToWrite(false);
			dynamic_cast<writeTextCommand*>(this->buttons[i]->getCommand(1))->execute();
		}
	}
	if (this->isRegister)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (i == this->selectedButton)
			{
				dynamic_cast<writeTextCommand*>(this->buttons[i]->getCommand(1))->setAbleToWrite(true);
			}
				
			else
				dynamic_cast<writeTextCommand*>(this->buttons[i]->getCommand(1))->setAbleToWrite(false);
			dynamic_cast<writeTextCommand*>(this->buttons[i]->getCommand(1))->execute();
		
		}
	}


	
}


void Login::updateClickButton(bool& held)
{

	if (this->selectedButton == -1)
		return;

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
		|| (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
	{
		if (held == false)
		{
			held = true;
			if (this->selectedButton >= 0)
			{
				if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->buttons[this->selectedButton]->isHoverMouse())
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					switch (selectedButton)
					{
					case 0:
						if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
						{
							break;
						}
						this->buttons[selectedButton]->changeHovered();
						this->selectedButton++;
						this->buttons[selectedButton]->changeHovered();
						break;
					case 1:
						if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
						{
							break;
						}
						if (!isRegister)
						{
							if (checkAccount())
							{
								this->buttons[selectedButton]->click();
							}
							this->isErrorLogin = true;
							break;
						}
						this->buttons[selectedButton]->changeHovered();
						this->selectedButton++;
						this->buttons[selectedButton]->changeHovered();
						break;


					case 2:
						if (!this->isRegister)
						{
							this->isRegister = true;
							this->updateRegisterAnimation = true;
							this->speedRegister = sqrt(pow(confirmPassWordButton->getPosition().x - registerButton->getPosition().x, 2) + pow(confirmPassWordButton->getPosition().y + 3 * confirmPassWordButton->getSize().y - registerButton->getPosition().y, 2)) / moveTime;
							this->speedconfirmPassWord = (2 * confirmPassWordButton->getSize().y) / moveTime;
							addConfirmButton();
							resetAfterRegister();
							break;
						}
						if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
						{
							break;
						}
						if (checkRegister())
						{
							this->buttons[selectedButton]->click();
						}
						this->isErrorRegister = true;
						break;

					case 3:
						this->buttons[selectedButton]->click();
						break;

					}
				}
			}
		}

	}
	else held = false;

}



void Login::updateBackgroundAnimation(float dt)
{
	this->loginAnimation->update(dt, false);
}

void Login::draw(sf::RenderWindow& window)
{
	this->loginAnimation->render(window, sf::Vector2f(0, 0));
	
	Scene::draw(window);

	for (int i = 0; i < this->hiddenTexts.size(); i++)
	{
		if (this->buttons[i]->getTextSize() != 0) continue;
		this->hiddenTexts[i]->draw(window);
	}
	if (this->isErrorLogin)
	{
		this->errorLogin.draw(window);
	}
	if (this->isErrorRegister)
	{
		this->errorRegister.draw(window);
	}
	
}

void Login::updateRegisterMovement(float dt)
{
	if (!this->updateRegisterAnimation) {
		return;
	}
	if (this->moveTime <= 0)
	{
		this->updateRegisterAnimation = false;
		this->selectedButton = -1;
		this->buttons.pop_back();
		return;
	}
	float angle = atan2(registerButton->getPosition().y - confirmPassWordButton->getPosition().y, registerButton->getPosition().x - confirmPassWordButton->getPosition().x);
	this->registerButton->move(sf::Vector2f(-speedRegister * cos(angle) * dt, -speedRegister * sin(angle) * dt));
	this->confirmPassWordButton->move(sf::Vector2f(0, speedconfirmPassWord * dt));
	this->hiddenConfirm.move(sf::Vector2f(0, speedconfirmPassWord * dt));
	this->moveTime -= dt;

}

void Login::update(float dt, bool& held)
{
	this->updateHoverButton();
	this->updateClickButton(held);
	//this->updateText();
	this->updateBackgroundAnimation(dt);
	this->updateRegisterMovement(dt);
}


void Login::render(sf::RenderWindow& window)
{
	
	this->draw(window);

}




void Login::addConfirmButton()
{
	if (!this->isRegister) return;
	this->registerButton->changeHovered();
	this->selectedButton = 4;
	this->buttons.insert(buttons.begin() + 2, confirmPassWordButton);
	std::swap(*(buttons.end() - 1), *(buttons.end() - 2));



}

void Login::resetAfterRegister()
{
	if (!this->isRegister) return;
	this->isErrorLogin = false;
	this->isErrorRegister = false;
	this->userNameButton->setText("");
	this->passwordButton->setText("");
	this->confirmPassWordButton->setText("");
	sf::Vector2f centerUser = userNameButton->getPosition() + userNameButton->getSize() / 2.0f;
	this->userNameButton->setButtonSize(sf::Vector2f(200, 50));
	this->userNameButton->setPosition(centerUser);
	sf::Vector2f centerPassword = passwordButton->getPosition() + passwordButton->getSize() / 2.0f;
	this->passwordButton->setButtonSize(sf::Vector2f(200, 50));
	this->passwordButton->setPosition(centerPassword);
	this->confirmPassWordButton->setButtonSize(sf::Vector2f(200, 50));
}

GameState Login::getNextScene()
{
	if (selectedButton == -1) return GameState::LOGIN;
	auto nextScene = dynamic_cast<changeSceneCommand*>(this->buttons[this->selectedButton]->getCommand(0));
	if (nextScene != nullptr)
	{
		return nextScene->getScene();
	}
}

Login::~Login()
{
	for (auto button : this->buttons)
	{
		delete button;
	}
	delete this->loginAnimation;
}


bool Login::checkAccount()
{
	std::string userName = this->userNameButton->getText();
	std::string passWord = this->passwordButton->getText();
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
	std::string userName = this->userNameButton->getText();
	std::string passWord = this->passwordButton->getText();
	std::string confirmPass = this->confirmPassWordButton->getText();
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