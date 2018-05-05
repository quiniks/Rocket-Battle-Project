#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "DynamicObject.h"

class DynamicSprite : public DynamicObject {
private:
	void update();
protected:
	sf::Sprite m_Sprite;
public:
	DynamicSprite(sf::Texture* p_Texture, float p_Restitution, sf::Vector2f p_Size, sf::Vector2f p_StartPos, float p_Density, float p_DragCo, float p_FricCo);
	~DynamicSprite();
	float area();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};