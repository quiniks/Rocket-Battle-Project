#include "..\include\Kinematic.h"

Kinematic::Kinematic()
{
}

Kinematic::~Kinematic()
{
}

sf::Vector2f Kinematic::getPosition()
{
	return m_Position;
}

sf::Vector2f Kinematic::getVelocity()
{
	return m_Velocity;
}

sf::Vector2f Kinematic::getAcceleration()
{
	return m_Acceleration;
}

void Kinematic::setPosition(sf::Vector2f p_Position)
{
	m_Position = p_Position;
}

void Kinematic::setVelocity(sf::Vector2f p_Velocity)
{
	m_Velocity = p_Velocity;
}

void Kinematic::setAcceleration(sf::Vector2f p_Acceleration)
{
	m_Acceleration = p_Acceleration;
}

void Kinematic::integrate(float p_DeltaTime)
{
	//semi-implicit euler
	m_Velocity += m_Acceleration * p_DeltaTime;
	m_Position += m_Velocity * p_DeltaTime;
}

void Kinematic::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}
