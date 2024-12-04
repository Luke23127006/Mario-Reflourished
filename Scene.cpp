#include "Scene.h"









Scene::Scene()
{
	this->selectedButton = 0;
	this->isPressedDown = false;
	this->isPressedUp = false;
	this->currentControlMode = ControlMode::KEYBOARD;
}


void Scene::update(float deltaTime, bool& held)
{
}




void Scene::updateClickButton(bool& held)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (held == false)
		{
			held = true;
			if (this->selectedButton >= 0)
			{
				if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->buttons[this->selectedButton]->isHoverMouse())
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{

					this->buttons[this->selectedButton]->click();
				}
			}
		}
	}
	else held = false;
}

void Scene::updateKeyBoardControl()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (!this->isPressedDown)
		{
			currentControlMode = ControlMode::KEYBOARD;
			this->buttons[this->selectedButton]->setHovered(false);
			this->selectedButton = (this->selectedButton + 1) % this->buttons.size();
			this->isPressedDown = true;
			std::cout << "Down\n";
		}
	}
	else {
		this->isPressedDown = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (!this->isPressedUp)
		{
			currentControlMode = ControlMode::KEYBOARD;
			this->buttons[this->selectedButton]->setHovered(false);
			this->selectedButton = (this->selectedButton - 1 + this->buttons.size()) % static_cast<int>(this->buttons.size());
			this->isPressedUp = true;
			std::cout << "Up\n";
		}
	}
	else {
		this->isPressedUp = false;
	}
}


void Scene::updateMouseControl()
{
	// Switch to use mouse
	if (sqrt(pow((MOUSE_VIEW_POSITION.x - MOUSE_VIEW_LAST_POSITION.x), 2) +
		pow((MOUSE_VIEW_POSITION.y - MOUSE_VIEW_LAST_POSITION.y), 2)) > 30.f ||
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		currentControlMode = ControlMode::MOUSE;
		MOUSE_VIEW_LAST_POSITION = MOUSE_VIEW_POSITION;

	}
	// Mouse hover
	if (currentControlMode == ControlMode::MOUSE)
	{
		for (int i = 0; i < this->buttons.size(); i++)
		{
			if (this->buttons[i]->isHoverMouse())
			{
				if (i == this->selectedButton)
				{
					break;
				}
				this->buttons[selectedButton]->setHovered(false);
				this->selectedButton = i;
			}
		}
	}
}
void Scene::colorButton()
{
	this->buttons[this->selectedButton]->setHovered(true);

	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->colorHoverButton();
	}
}
void Scene::updateHoverButton()
{
	this->updateKeyBoardControl();
	this->updateMouseControl();
	this->colorButton();
}




void Scene::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->draw(window);
	}
}