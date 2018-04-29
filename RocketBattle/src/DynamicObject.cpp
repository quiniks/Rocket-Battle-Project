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
