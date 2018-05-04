#pragma once

#include <SFML/Graphics.hpp>
#include "Kinematic.h"

class DynamicObject : public Kinematic {
protected:
	float m_Density = 1.0f;
	virtual float area() = 0;
	float m_Mass = 1.0f;
	float m_Restitution = 0.0f;
	float m_DragCoefficient =  0.0f;
	float m_FrictionCoefficient = 0.0f;
	float m_MomentOfInertia = 1.0f;
	sf::FloatRect m_BoundingBox;
public:
	DynamicObject();
	~DynamicObject();
	void setRestitution(float p_Restitution);
	float getRestitution();
	void setDragCo(float p_DragCoefficient);
	float getDragCo();
	void setFrictionCo(float p_FricCoefficient);
	float getFricCo();
	float getMomentOfInertia();
	float getMass();
	void applyForce(sf::Vector2f p_Force);
	sf::FloatRect getBoundBox();
};