/*!
@file DynamicPixel.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "DynamicObject.h"

/* \class DynamicPixel
\brief
*/

class DynamicPixel : DynamicObject {
protected:
	float m_LifeTime;
public:
	DynamicPixel(float p_LifeTime, sf::Vector2f p_Accel, sf::Vector2f p_Vel, sf::Vector2f p_Pos);
	~DynamicPixel();
};