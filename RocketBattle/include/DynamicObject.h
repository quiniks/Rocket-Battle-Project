#pragma once

#include <SFML/Graphics.hpp>
#include "Kinematic.h"

class DynamicObject : public Kinematic {
protected:
	//float m_Density;
	//virtual float area();
	float m_Restitution;
	float m_Friction;
public:
	DynamicObject();
	~DynamicObject();
	void setRestitution(float p_Restitution);
	float getRestitution();
	//Add friction
};