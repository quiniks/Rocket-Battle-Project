/*!
@file AimLine.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

/* \class AimLine
\brief A class that creates, updates and draws an aiming reticle
*/

class AimLine : public sf::Drawable {
private:
	sf::VertexArray m_Vertices; //!< The vertices to be drawn
	float m_StartRadius = 25.0f; //!< The distance from the centre to the start of the line
	float m_MaxMag = 50.0f; //!< The max length of the drawn line
	float m_Multiplier = 0.0f; //!< The multiplier value of magnitude
	sf::Vector2f m_DirUnitVector; //!< The unit direction vector of the line
public:
	AimLine(); //!< Default constructor
	~AimLine(); //!< Destructor
	float getMultiplier(); //!< get the multiplier value
	sf::Vector2f getDirUnit(); //!< get the unit direction vector
	/*!
	* update the vertices
	* @param[in] p_Target the target position
	* @param[in] p_Start the start position
	*/
	void update(sf::Vector2f p_Target, sf::Vector2f p_Start);
	/*!
	* Draw
	* @param[in, out] target Render target to draw to
	* @param[in] states Render state
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};