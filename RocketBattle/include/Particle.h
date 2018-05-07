/*!
@file Particle.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "DynamicObject.h"

/* \class Particle
\brief A dynamic object that keeps track of how long it exists for and its previous position
*/

class Particle : public DynamicObject {
private:
	void update(); //!< Updates last position and applys drag
protected:
	float m_LifeTime = 0.0f; //!< The time left
	sf::Vector2f m_LastPosition = sf::Vector2f(0.0f, 0.0f); //!< The particles last position
public:
	/*!
	* Constructor
	* @param[in] p_LifeTime Initial life time
	* @param[in] p_Accel Intial acceleration
	* @param[in] p_Vel Initial velocity
	* @param[in] p_Pos Initial position
	* @param[in] p_Restitution Initial bounciness
	* @param[in] p_Density Initial density
	* @param[in] p_DragCo Intial drag coefficient
	*/
	Particle(float p_LifeTime, sf::Vector2f p_Accel, sf::Vector2f p_Vel, sf::Vector2f p_Pos, float p_Restitution, float p_Density, float p_DragCo);
	/*!
	* Set the last position
	* @param[in] p_Position Position
	*/
	void setLastPos(sf::Vector2f p_Position);
	sf::Vector2f getLastPos(); //!< Get the last position
	/*!
	* Set the particles life to a set amount of time
	* @param[in] p_Time time amount
	*/
	void setLife(float p_Time);
	float getLife(); //!< get the current life time
	float area(); //!< return the area of a particle
	/*!
	* Draw
	* @param[in, out] target Render target to draw to
	* @param[in] states Render state
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	~Particle(); //!< Destructor
};