/*!
@file Kinematic.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

/* \class Kinematic
\brief
*/

class Kinematic : public sf::Drawable {
private:
	void integrate(float p_DeltaTime);
protected:
	sf::Vector2f m_Position = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f m_Velocity = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f m_Acceleration = sf::Vector2f(0.0f, 0.0f);

	float m_Rotation = 0.0f;
	float m_AngularVelocity = 0.0f;
	float m_AngularAcceleration = 0.0f;

	virtual void UpdateChild() = 0;
public:
	Kinematic();
	~Kinematic();
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	sf::Vector2f getAcceleration();
	void setPosition(sf::Vector2f p_Position);
	void setVelocity(sf::Vector2f p_Velocity);
	void setAcceleration(sf::Vector2f p_Acceleration);
	void setRotation(float p_Rotation);
	void setAngularVel(float p_AngularVel);
	void setAngularAccel(float p_AngularAccel);
	void Update(float p_DeltaTime);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
};