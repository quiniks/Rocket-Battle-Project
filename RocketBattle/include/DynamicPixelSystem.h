/*!
@file DynamicPixelSystem.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "DynamicPixel.h"

/* \class DynamicPixelSystem
\brief
*/

class DynamicPixelSystem : public sf::Drawable {
private:
	std::vector<DynamicPixel> m_vDynamicPixels;
public:
	DynamicPixelSystem();
	~DynamicPixelSystem();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};