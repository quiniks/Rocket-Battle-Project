/*!
@file DynamicObject.h
*/

#pragma once

#include <SFML/Graphics.hpp>

/* \class DynamicObject
\brief
*/

class DynamicObject : sf::Drawable {
protected:
	sf::Vector2f m_Position = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f m_Velocity = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f m_Acceleration = sf::Vector2f(0.0f, 0.0f);
public:
	DynamicObject();
	~DynamicObject();
	void setPosition(sf::Vector2f p_Position);
	void setVelocity(sf::Vector2f p_Velocity);
	void setAcceleration(sf::Vector2f p_Acceleration);
	void integrate(float p_Time);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};