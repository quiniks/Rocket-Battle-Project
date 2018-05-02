#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "DynamicObject.h"

class Rocket : public DynamicObject {
private:
	void UpdateChild();
protected:
	sf::Sprite m_Sprite;
	sf::RectangleShape m_BoundingBox;
public:
	Rocket(sf::Texture* p_Texture, float p_Restitution, sf::Vector2f p_Size, sf::Vector2f p_StartPos, float p_Oriention);
	~Rocket();
	void setTexture(sf::Texture* p_Texture);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};