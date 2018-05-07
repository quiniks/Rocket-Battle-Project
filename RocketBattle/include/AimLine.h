#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class AimLine : public sf::Drawable {
private:
	sf::VertexArray m_Vertices;
	float m_StartRadius = 25.0f;
	float m_MaxMag = 50.0f;
	float m_Multiplier = 0.0f;
	sf::Vector2f m_DirUnitVector;
public:
	AimLine();
	~AimLine();
	float getMultiplier();
	sf::Vector2f getDirUnit();
	void update(sf::Vector2f p_Target, sf::Vector2f p_Start);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};