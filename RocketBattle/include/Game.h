/*!
@file Game.h
*/

#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

#include "TextureLoader.h"
#include "Terrain.h"
#include "ParticleSystem.h"
#include "Rocket.h"
#include "AimLine.h"
#include "DynamicSprite.h"

class Game : public sf::Drawable {
private:
	sf::View m_View;
	sf::Vector2u m_CameraSize = sf::Vector2u(800, 600);
	sf::Vector2f m_Gravity = sf::Vector2f(0.0f, 9.81f);
	TextureLoader* m_TextureLoader;
	Terrain m_Terrain;
	ParticleSystem m_ParticleSystem;
	std::vector<Rocket> m_Rockets;
	std::vector<DynamicSprite> m_Bullets;
	sf::Vector2f m_MouseWorldPos;
	bool m_Debug = false;
	enum  Teams { neutral, red, blue };
	int m_Turn = 0;
	AimLine m_AimLine;
	Rocket* m_PlayerRocket;
	void handleInputPerUpdate();
public:
	Game(sf::RenderWindow& p_Window);
	~Game();
	void handleKeyboardInput(int key);
	void handleMouseInput(sf::Mouse::Button button);
	void handleMouseMove(const sf::RenderWindow& p_Window);
	void update(float p_TimeStep);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool getDebug();
};
