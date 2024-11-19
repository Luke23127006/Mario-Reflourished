#include <SFML\Graphics.hpp>
#include<iostream>
#include "UserInterface.h"
#include "Button.h"





class SelectLevel : public Scene
{
private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	Button level1Button;
	Button level2Button;
	Button level3Button;
	Button backButton;
	std::vector<Button*> buttons;
	int selectedButton;
	bool isPressedUp;
	bool isPressedDown;
	bool goToLevel1;
	bool goToLevel2;
	bool goToLevel3;
	bool backToPlay;

public:
	SelectLevel(sf::RenderTexture& window);
	void loadTexture();
	void updateHoverButton(sf::RenderWindow& window);
	void updateClickButton(sf::RenderWindow& window, bool& held);
	void draw(sf::RenderWindow& window);	
	void render(sf::RenderWindow& window, bool& held) override;
	GameState getNextScene() override;

};