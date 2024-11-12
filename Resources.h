#pragma once

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

	void initTextures();
	void initFonts();
	void initSounds();

	Resources();
	virtual ~Resources();
};

