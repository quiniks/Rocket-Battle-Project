/*!
@file DynamicPixelSystem.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "DynamicPixel.h"
#include <stdlib.h>

/* \class DynamicPixelSystem
\brief
*/

class DynamicPixelSystem : public sf::Drawable {
private:
	std::vector<DynamicPixel> m_DynamicPixels;
	sf::VertexArray m_Vertices;
public:
	DynamicPixelSystem();
	~DynamicPixelSystem();
	void Explosion(sf::Vector2f p_Position, sf::Vector2f p_Acceleration, float p_InitialSpeed, unsigned int p_Amount, float p_LifeTime);
	void Update(float p_DeltaTime);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};