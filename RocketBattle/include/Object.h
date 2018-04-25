/*!
@file Object.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

/* \class Object
\brief 
*/

class Object : public sf::Drawable {
protected:
	sf::Vector2f m_Position;
	sf::Vector2f m_Size;
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
};