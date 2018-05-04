#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "DynamicObject.h"

class Rocket : public DynamicObject {
private:
	void update();
protected:
	sf::Sprite m_Sprite;
	int m_Team;
public:
	Rocket(sf::Texture* p_Texture, float p_Restitution, sf::Vector2f p_Size, sf::Vector2f p_StartPos, float p_Density, float p_DragCo, float p_FricCo, int p_Team);
	~Rocket();
	void setTexture(sf::Texture* p_Texture);
	float area();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};