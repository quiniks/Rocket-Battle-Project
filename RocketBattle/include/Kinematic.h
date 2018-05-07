/*!
@file Kinematic.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

/* \class Kinematic
\brief A class that provides methods to create motion using position, velocity and acceleration
*/

class Kinematic : public sf::Drawable {
private:
	void integrate(float p_DeltaTime); //!< intergrate method updates position based off velocity and acceleration
protected:
	sf::Vector2f m_Position = sf::Vector2f(0.0f, 0.0f); //!< Position of object
	sf::Vector2f m_Velocity = sf::Vector2f(0.0f, 0.0f); //!< Velocity  of object
	sf::Vector2f m_Acceleration = sf::Vector2f(0.0f, 0.0f); //!< Acceleration of object

	float m_Rotation = 0.0f; //!< Rotation of object
	float m_AngularVelocity = 0.0f; //!< Angular velocity of object
	float m_AngularAcceleration = 0.0f; //!< Angular acceleration Rotation of object

	virtual void update() = 0; //!< late binding update function to update child objects
public:
	Kinematic(); //!< Default constructor
	~Kinematic(); //!< Destructor
	sf::Vector2f getPosition(); //!< Get current position
	sf::Vector2f getVelocity(); //!< Get current velocity
	sf::Vector2f getAcceleration(); //!< Get current acceleration

	float getAngularVel(); //!< Get current angular velocity
	/*!
	* Apply an acceleration
	* @param[in] p_Acceleration Acceleration
	*/
	void applyAcceleration(sf::Vector2f p_Acceleration);
	/*!
	* Set position
	* @param[in] p_Position position
	*/
	void setPosition(sf::Vector2f p_Position);
	/*!
	* Set velocity
	* @param[in] p_Velocity position
	*/
	void setVelocity(sf::Vector2f p_Velocity);
	//void setAcceleration(sf::Vector2f p_Acceleration);
	//void setRotation(float p_Rotation);
	//void setAngularVel(float p_AngularVel);
	//void setAngularAccel(float p_AngularAccel);
	/*!
	* Update function that calls the child's update function, intergrates and resets acceleration to 0
	* @param[in] p_Velocity position
	*/
	void polyUpdate(float p_DeltaTime);
	/*!
	* Draw
	* @param[in, out] target Render target to draw to
	* @param[in] states Render state
	*/
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
};