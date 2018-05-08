/*!
@file GameOver.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Scene.h"
#include "TextureLoader.h"
#include "TextButton.h"
#include "Menu.h"

/*! \class GameOver
\brief A menu scene that displays some useful info and allows you to start the game
*/

class GameOver : public Scene {
private:
	sf::Font m_PixelFont; //!< Font to be used
	sf::Text m_Title; //!< Title text to be displayed
	TextButton* m_MenuButton; //!< return to menu button
public:
	/*!
	* Constructor
	* @param[in] p_WindowSize initial window size
	* @param[in] p_Winner the string to be displayed
	* @param[in] p_Color the text color
	*/
	GameOver(sf::Vector2u p_WindowSize, std::string p_Winner, sf::Color p_Color);
	~GameOver();
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