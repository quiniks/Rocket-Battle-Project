/*!
@file TextureLoader.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <Windows.h>
#include <iostream>

/* \class TextureLoader
\brief A singleton loader class that prevents any unnecessary copying of potentially large texture files
*/

class TextureLoader
{
private:
	TextureLoader();	//!< Private constructor
	static TextureLoader * m_spInstance;	//!< Static pointer to the singleton texture loader
	std::map<std::string, sf::Texture *> m_Textures;	//!< Map container for textures
	~TextureLoader();	//!< Private destructor
public:
	static TextureLoader * instance();	//!< Returns a pointer to the static texture loader
	sf::Texture * getTexture(const std::string& p_Key);	//!< Returns a texture with the specified key
	void loadTextures(const std::string& p_FilePath);	//!< Loads textures from the specified directory
	TextureLoader(TextureLoader const&) = delete; //!< prevents the creation of multiple texture loaders
	TextureLoader& operator=(TextureLoader const&) = delete; //!< prevents the creation of multiple texture loaders
};