#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include "Global.h"

class Resources
{
public:
	static std::map<std::string, sf::Texture> textures;
	static std::map<std::string, sf::Font> fonts;
	static std::map<std::string, sf::SoundBuffer> sounds;
	static std::map<int, sf::Color> getColor;

	void initTextures();
	void initFonts();
	void initSounds();
	void initColors();

	Resources();
	virtual ~Resources();
};

