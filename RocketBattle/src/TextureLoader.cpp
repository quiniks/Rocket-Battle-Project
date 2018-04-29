#include "TextureLoader.h"

/**
@file TextureLoader.cpp
*/

//make the instance a nullptr intially
TextureLoader * TextureLoader::m_spInstance = nullptr;

TextureLoader::TextureLoader()
{

}

TextureLoader::~TextureLoader()
{
	delete m_spInstance;
	m_spInstance = nullptr;
	for (auto& pair : m_Textures) {
		delete pair.second;
		pair.second = nullptr;
	}
}

TextureLoader * TextureLoader::instance()
{
	if (m_spInstance == nullptr) {
		m_spInstance = new TextureLoader();
	}
	return m_spInstance;
}

sf::Texture * TextureLoader::getTexture(const std::string& p_String)
{
	if (m_Textures.count(p_String)) {
		
		return m_Textures.at(p_String);
	}
	std::cout << "Texture does not exist" << std::endl;
	return nullptr;
}

void TextureLoader::loadTextures(const std::string& p_FilePath)
{
	//Reference: http://www.martinbroadhurst.com/list-the-files-in-a-directory-in-c.html
	std::string l_Wildcard = p_FilePath;
	l_Wildcard.append("\\*");

	WIN32_FIND_DATA l_FileData;
	HANDLE l_hFind;
	l_hFind = FindFirstFile(l_Wildcard.c_str(), &l_FileData);
	if (l_hFind != INVALID_HANDLE_VALUE) {
		std::cout << "Loading textures:" << std::endl;
		do {
			const std::string& key = l_FileData.cFileName;
			if (key != "." && key != "..") {
				m_Textures[key] = new sf::Texture();
				if (!m_Textures[key]->loadFromFile(p_FilePath + "\\" + key)) {
					delete m_Textures[key];
					m_Textures[key] = nullptr;
					m_Textures.erase(key);
				}
				else {
					std::cout << key << " loaded" << std::endl;
				}
			}
		} while (FindNextFile(l_hFind, &l_FileData) != 0);
	}
	else {
		std::cout << "No directory found" << std::endl;
	}
	FindClose(l_hFind);
}

