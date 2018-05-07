/*!
@file Game.h
*/

#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <list>

#include "TextureLoader.h"
#include "Terrain.h"
#include "ParticleSystem.h"
#include "Rocket.h"
#include "AimLine.h"
#include "Projectile.h"
#include "Scene.h"
#include "GameOver.h"

/* \class Game
\brief A game scene that runs the rocket battle game
*/

class Game : public Scene {
private:
	sf::View m_MiniView; //!< the mini map view
	sf::RectangleShape m_ViewArea; //!< a rectangle that highlights the viewable area in the minimap

	sf::Sprite m_PauseSprite; //!< The pause sprite to be displayed
	enum State { running, paused }; //!< The game states
	int m_State = running; //!< The initial state is running

	sf::Vector2f m_Gravity = sf::Vector2f(0.0f, 9.81f); //!< The gravity

	enum  Teams { neutral, red, blue }; //!< The teams
	int m_RocketIndex = 0; //!< The current rocket index
	int m_TeamTurn = Teams::red; //!< The initial turn goes to red team

	AimLine m_AimLine; //!< The aiming reticle
	Rocket* m_PlayerRocket; //!< A pointer to the current rocket in m_Rockets
	bool m_HasShot = false; //!< Has the player shot?
	bool m_Moving = false; //!< Is the player moving?

	TextureLoader* m_TextureLoader; //!< Pointer to the texture loader instance
	Terrain m_Terrain; //!< The terrain
	ParticleSystem m_ParticleSystem; //!< The particle system
	std::vector<Rocket> m_Rockets; //!< A vector of all the rockets
	std::vector<Projectile> m_Bullets; //!< A vector of all the bullets

	void handleInputPerUpdate(); //!< Handle keyboard input every update frame
	void passTurn(); //!< Check if game is over and change the playable rocket to whoever is next in line
public:
	/*!
	* Constructor
	* @param[in] p_WindowSize Initial window size
	*/
	Game(sf::Vector2u p_WindowSize);
	~Game();
	/*!
	* handle keyboard events
	* @param[in] p_Key the key that was pressed
	*/
	void handleKeyboardInput(int p_Key);
	/*!
	* handle mouse button events
	* @param[in] p_Button the button that was pressed
	*/
	void handleMouseInput(sf::Mouse::Button p_Button);
	/*!
	* update the menu
	* @param[in] p_TimeStep time elapsed since last frame
	*/
	void update(float p_TimeStep);
	/*!
	* Draw
	* @param[in, out] target Render target to draw to
	* @param[in] states Render state
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
