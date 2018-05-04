/*!
@file Particle.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "DynamicObject.h"

/* \class Particle
\brief
*/

class Particle : public DynamicObject {
private:
	void update();
protected:
	float m_LifeTime = 0.0f;
	sf::Vector2f m_LastPosition = sf::Vector2f(0.0f, 0.0f);
public:
	Particle(float p_LifeTime, sf::Vector2f p_Accel, sf::Vector2f p_Vel, sf::Vector2f p_Pos, float p_Restitution, float p_Density, float p_DragCo);
	void setLastPos(sf::Vector2f p_Position);
	sf::Vector2f getLastPos();
	void setLife(float p_Time);
	float getLife();
	float area();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	~Particle();
};