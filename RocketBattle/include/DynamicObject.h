/*!
@file DynamicObject.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "Kinematic.h"

/*! \class DynamicObject
\brief A kinematic rectangle that can be affected by forces
*/

class DynamicObject : public Kinematic {
protected:
	float m_Density = 1.0f; //!< The density
	virtual float area() = 0; //!< late binding area getter
	float m_Mass = 1.0f; //!< The mass
	float m_Restitution = 0.0f; //!< The restitution
	float m_DragCoefficient =  0.0f; //!< The default drag coefficient
	float m_FrictionCoefficient = 0.0f; //!< The default friction coefficient
	float m_MomentOfInertia = 1.0f; //!< The default moment of inertia;
	sf::FloatRect m_BoundingBox; //!< The bounding box
public:
	DynamicObject(); //!< Default constructor
	~DynamicObject(); //!< Destructor
	 /*!
	 * set Restitution
	 * @param[in] p_Restitution the bounciness value
	 */
	void setRestitution(float p_Restitution);
	float getRestitution(); //!< get restitution
	/*!
	* set drag coefficient
	* @param[in] p_DragCoefficient the drag coefficient
	*/
	void setDragCo(float p_DragCoefficient);
	float getDragCo(); //!< get drag coefficient
	/*!
	* set friction coefficient
	* @param[in] p_FricCoefficient the friction coefficient
	*/
	void setFrictionCo(float p_FricCoefficient);
	float getFricCo(); //!< get friction coefficient
	float getMomentOfInertia(); //!< get moment of inertia
	float getMass(); //!< get mass
	/*!
	* apply a force
	* @param[in] p_Force the force to be applied
	*/
	void applyForce(sf::Vector2f p_Force);
	sf::FloatRect getBoundBox(); //!< get the bounding box
};