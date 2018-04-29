/*!
@file Game.h
*/

#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

#include "TextureLoader.h"
#include "Terrain.h"
#include "ParticleSystem.h"

class Game : public sf::Drawable {
private:
	sf::View m_View;
	sf::Vector2f m_CameraSize = sf::Vector2f(800.0f, 600.0f);
	sf::Vector2f m_Gravity = sf::Vector2f(0.0f, 9.81f);
	TextureLoader* m_TextureLoader;
	Terrain m_Terrain;
	ParticleSystem m_ParticleSystem;

	sf::Vector2f m_MouseWorldPos;
	bool m_Debug = false;
public:
	Game();
	~Game();
	void handleKeyboardInput(int key);
	void handleMouseInput(sf::Mouse::Button button);
	void handleMouseMove(const sf::RenderWindow& p_Window);
	void update(float p_TimeStep);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool getDebug();
};
