#include "..\include\DynamicObject.h"

DynamicObject::DynamicObject()
{
}

DynamicObject::~DynamicObject()
{
}

void DynamicObject::setRestitution(float p_Restitution) {
	m_Restitution = p_Restitution;
}

float DynamicObject::getRestitution()
{
	return m_Restitution;
}

void DynamicObject::setDragCo(float p_DragCoefficient)
{
	m_DragCoefficient = p_DragCoefficient;
}

float DynamicObject::getDragCo()
{
	return m_DragCoefficient;
}

void DynamicObject::setFrictionCo(float p_FricCoefficient)
{
	m_FrictionCoefficient = p_FricCoefficient;
}

float DynamicObject::getFricCo()
{
	return m_FrictionCoefficient;
}

float DynamicObject::getMomentOfInertia()
{
	return m_MomentOfInertia;
}

float DynamicObject::getMass()
{
	return m_Mass;
}

void DynamicObject::applyForce(sf::Vector2f p_Force)
{
	m_Acceleration += (p_Force / m_Mass);
}

sf::FloatRect DynamicObject::getBoundBox()
{
	return m_BoundingBox;
}
