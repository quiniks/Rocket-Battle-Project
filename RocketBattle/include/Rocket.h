/*!
@file Rocket.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "DynamicObject.h"

/*! \class Rocket
\brief A playable rocket class that keeps track of fuel and life
*/

class Rocket : public DynamicObject {
private:
	void update(); //!< Updates the sprite position and applys drag
protected:
	sf::Sprite m_Sprite; //!< Sprite to draw rocket texture
	int m_Team = 0; //!< Team value
	float m_MaxLife = 100.0f; //!< Maximum life
	float m_Life = 0.0f; //!< Current life
	float m_LifeBarMaxLength; //!< Life bar's max length
	sf::RectangleShape m_LifeBar; //!< Life bar rectangle
	sf::Vector2f m_LifeBarOffset; //!< Life bar Offset from the rocket position
	float m_MaxFuel = 250.0f; //!< Maximum fuel
	float m_Fuel = 0.0f; //!< Current fuel
	float m_FuelBarMaxLength; //!< Fuel bar's max length
	sf::RectangleShape m_FuelBar; //!< Fuel bar's rectangle
	sf::Vector2f m_FuelBarOffset; //!< Fuel bar offset from rocket position
public:
	/*!
	* Constructor
	* @param[in] p_Texture Initial texture
	* @param[in] p_Restitution Intial bounciness
	* @param[in] p_Size Initial size of the the axis aligned bounding box
	* @param[in] p_StartPos Initial position of the rocket
	* @param[in] p_Density Initial density
	* @param[in] p_DragCo Intial drag coefficient
	* @param[in] p_FricCo Intial friction coefficient
	* @param[in] p_Team Initial team
	*/
	Rocket(sf::Texture* p_Texture, float p_Restitution, sf::Vector2f p_Size, sf::Vector2f p_StartPos, float p_Density, float p_DragCo, float p_FricCo, int p_Team);
	~Rocket(); //!< Destructor
	/*!
	* Set the texture
	* @param[in] p_Texture Chosen texture to switch to
	*/
	void setTexture(sf::Texture* p_Texture);
	/*!
	* Set the life
	* @param[in] p_Life life value
	*/
	void setLife(float p_Life);
	float getLife(); //!< get life
	 /*!
	 * set the fuel
	 * @param[in] p_Fuel fuel value
	 */
	void setFuel(float p_Fuel);
	float getFuel(); //!< get fuel
	int getTeam(); //!< get team
	float area(); //!< returns the area
	/*!
	* Draw
	* @param[in, out] target Render target to draw to
	* @param[in] states Render state
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};