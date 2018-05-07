/*!
@file TextButton.h
*/


#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

/* \class TextButton
\brief A Wrapper class for sf::Text and sf::Font that adds a mosue over checker
*/

class TextButton : public sf::Drawable {
private:
	sf::Font m_Font; //!< The text box's font
	sf::Text m_Text; //!< The text box
	sf::Color m_BaseColor; //!< The text's default color
	sf::Color m_OverColor; //!< Change to this color when the mouse is over it
public:
	/*!
	* Constructor with initial values
	* @param[in] p_Font The font to use
	* @param[in] p_String The string to be displayed
	* @param[in] p_CharSize Character size
	* @param[in] p_BaseColor Default color
	* @param[in] p_OverColor Mouse over color
	*/
	TextButton(sf::Font p_Font, std::string p_String, float p_CharSize, sf::Color p_BaseColor, sf::Color p_OverColor);
	~TextButton(); //!< Destructor
	 /*!
	 * Set the position of the text
	 * @param[in] p_Position Chosen position
	 */
	void setPosition(sf::Vector2f p_Position);
	/*!
	* Update the buttons color based on mouse position
	* @param[in] p_MousePos The current position of the mouse
	*/
	void update(sf::Vector2f p_MousePos);
	/*!
	* Check if mouse is over the text button
	* @param[in] p_MousePos The current position of the mouse
	*/
	bool isMouseOver(sf::Vector2f p_MousePos);
	/*!
	* Draw
	* @param[in, out] target Render target to draw to
	* @param[in] states Render state
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};