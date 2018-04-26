#include "..\include\DynamicObject.h"

DynamicObject::DynamicObject()
{
}

DynamicObject::~DynamicObject()
{
}

void DynamicObject::setPosition(sf::Vector2f p_Position)
{
	m_Position = p_Position;
}

void DynamicObject::setVelocity(sf::Vector2f p_Velocity)
{
	m_Velocity = p_Velocity;
}

void DynamicObject::setAcceleration(sf::Vector2f p_Acceleration)
{
	m_Acceleration = p_Acceleration;
}

void DynamicObject::integrate(float p_DeltaTime)
{
	//semi-implicit euler
	m_Velocity += m_Acceleration * p_DeltaTime;
	m_Position += m_Velocity * p_DeltaTime;
}
