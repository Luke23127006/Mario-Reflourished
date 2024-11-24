#pragma once

#include "Global.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>

class Resources
{
public:
	static std::map<std::string, sf::Texture> textures;
	static std::map<std::string, sf::Font> fonts;
	static std::map<std::string, sf::SoundBuffer> sounds;

	static void initResources();
	static void initTextures();
	static void initFonts();
	static void initSounds();

	Resources();
	virtual ~Resources();
};

