/*!
@file Game.h
*/

#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

#include "TextureLoader.h"
#include "Terrain.h"
#include "DynamicPixelSystem.h"

class Game : public sf::Drawable {
private:
	sf::View m_View;
	sf::Vector2f m_WorldSize = sf::Vector2f(8.0f, 6.0f);
	sf::Vector2f m_WorldCentre = sf::Vector2f(0.0f, 0.0f);
	TextureLoader* m_TextureLoader;
	Terrain m_Terrain;
	DynamicPixelSystem m_DPS;
public:
	Game();
	~Game();
	void handleInput();
	void update(float p_TimeStep);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
