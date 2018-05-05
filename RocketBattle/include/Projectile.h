#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "DynamicObject.h"

class Projectile : public DynamicObject {
private:
	void update();
protected:
	sf::Sprite m_Sprite;
	float m_Damage;
public:
	Projectile(sf::Texture* p_Texture, float p_Restitution, sf::Vector2f p_Size, sf::Vector2f p_StartPos, float p_Density, float p_DragCo, float p_FricCo, float p_Damage);
	~Projectile();
	float area();
	float getDamage();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};