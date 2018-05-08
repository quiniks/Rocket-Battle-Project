/*!
@file Projectile.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "DynamicObject.h"

/*! \class Projectile
\brief A dynamic object that has damage
*/

class Projectile : public DynamicObject {
private:
	void update(); //!< Update sprite
protected:
	sf::Sprite m_Sprite; //!< Sprite to draw projectile texture
	float m_Damage; //!< Damage value
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
	* @param[in] p_Damage Initial damage value
	*/
	Projectile(sf::Texture* p_Texture, float p_Restitution, sf::Vector2f p_Size, sf::Vector2f p_StartPos, float p_Density, float p_DragCo, float p_FricCo, float p_Damage);
	~Projectile(); //!< Destructor
	float area(); //!< Return area
	float getDamage(); //!< Get damage value
	/*!
	* Draw
	* @param[in, out] target Render target to draw to
	* @param[in] states Render state
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};