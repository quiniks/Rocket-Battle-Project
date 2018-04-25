/*!
@file DynamicPixel.h
*/

#pragma once

#include <SFML/Graphics.hpp>

/* \class DynamicPixel
\brief
*/

class DynamicPixel : public sf::Drawable {
protected:
	sf::Vector2f m_Velocity;
	float m_LifeTime;
	sf::Vertex m_Vertex;
public:
	DynamicPixel();
	~DynamicPixel();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};