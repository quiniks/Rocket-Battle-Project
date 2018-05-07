#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "DynamicObject.h"

class Rocket : public DynamicObject {
private:
	void update();
protected:
	sf::Sprite m_Sprite;
	int m_Team = 0;
	float m_MaxLife = 100.0f;
	float m_Life = 0.0f;
	float m_LifeBarMaxLength;
	sf::RectangleShape m_LifeBar;
	sf::Vector2f m_LifeBarOffset;
	float m_MaxFuel = 250.0f;
	float m_Fuel = 0.0f;
	float m_FuelBarMaxLength;
	sf::RectangleShape m_FuelBar;
	sf::Vector2f m_FuelBarOffset;
public:
	Rocket(sf::Texture* p_Texture, float p_Restitution, sf::Vector2f p_Size, sf::Vector2f p_StartPos, float p_Density, float p_DragCo, float p_FricCo, int p_Team);
	~Rocket();
	void setTexture(sf::Texture* p_Texture);
	void setLife(float p_Life);
	float getLife();
	void setFuel(float p_Fuel);
	float getFuel();
	int getTeam();
	float area();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};