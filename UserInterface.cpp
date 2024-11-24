#include "UserInterface.h"









Scene::Scene()
{
	this->selectedButton = -1;
	this->isPressedDown = false;
	this->isPressedUp = false;
}


void Scene::update(float deltaTime)
{
}
void Scene::updateHoverButton(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (!this->isPressedDown)
		{
			if (this->selectedButton != -1)
				(*this->buttons[this->selectedButton]).changeHovered();
			this->selectedButton = (this->selectedButton + 1) % this->buttons.size();
			(*this->buttons[this->selectedButton]).changeHovered();
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
			if (this->selectedButton != -1)
				(*this->buttons[this->selectedButton]).changeHovered();
			else {
				this->selectedButton = static_cast<int>(this->buttons.size());
			}
			this->selectedButton = (this->selectedButton - 1 + this->buttons.size()) % static_cast<int>(this->buttons.size());
			(*this->buttons[this->selectedButton]).changeHovered();
			this->isPressedUp = true;
			std::cout << "Up\n";
		}
	}
	else {
		this->isPressedUp = false;
	}
	// Mouse hover
	for (int i = 0; i < this->buttons.size(); i++)
	{
		if (this->buttons[i]->isHoverMouse(window))
		{
			if (i == this->selectedButton)
			{
				break;
			}
			if (this->selectedButton != -1)
				this->buttons[this->selectedButton]->changeHovered();
			this->selectedButton = i;
			this->buttons[i]->changeHovered();
		}
	}


	// Color Button
	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->colorHoverButton(window);
	}
}

void Scene::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->draw(window);
	}
}