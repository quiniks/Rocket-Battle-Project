/*!
@file TextureLoader.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <Windows.h>
#include <iostream>

/*! \class TextureLoader
\brief A singleton loader class that prevents any unnecessary copying of potentially large texture files
*/

class TextureLoader
{
private:
	TextureLoader();	//!< Private constructor
	static TextureLoader * m_Instance;	//!< Static pointer to the singleton texture loader
	std::map<std::string, sf::Texture *> m_Textures;	//!< Map container for textures
	~TextureLoader();	//!< Private destructor
public:
	static TextureLoader * instance();	//!< Returns a pointer to the static texture loader
	/*!
	* Returns a texture with the specified key
	* @param[in] p_Key String address to the file
	*/
	sf::Texture * getTexture(const std::string& p_Key);
	/*!
	* Loads textures from the specified directory
	* @param[in] p_FilePath Path to a chosen directory
	*/
	void loadTextures(const std::string& p_FilePath);
	TextureLoader(TextureLoader const&) = delete; //!< prevents the creation of multiple texture loaders
	TextureLoader& operator=(TextureLoader const&) = delete; //!< prevents the creation of multiple texture loaders
};