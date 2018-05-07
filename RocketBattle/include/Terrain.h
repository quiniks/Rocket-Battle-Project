/*!
@file Terrain.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

/* \class Terrain
\brief
*/

class Terrain : public sf::Drawable {
private:
	sf::Image m_Image;
	sf::Texture* m_Texture;
	sf::RenderTexture m_RenderTexture;
	sf::Sprite m_Foreground;
	sf::Sprite m_Background;
public:
	Terrain();
	~Terrain();
	void LoadTerrain(sf::Texture* p_ForegroundTexture, sf::Texture* p_BackgroundTexture);
	sf::Vector2f GetNormal(int p_X, int p_Y, int p_Radius);
	bool isPixelEmpty(sf::Vector2i m_Pos);
	void SubtractShape(sf::Shape& p_Shape);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};