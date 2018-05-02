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

void Kinematic::setRotation(float p_Rotation)
{
	m_Rotation = p_Rotation;
}

void Kinematic::setAngularVel(float p_AngularVel)
{
	m_AngularVelocity = p_AngularVel;
}

void Kinematic::setAngularAccel(float p_AngularAccel)
{
	m_AngularAcceleration = p_AngularAccel;
}

void Kinematic::integrate(float p_DeltaTime)
{
	//semi-implicit euler
	m_Velocity += m_Acceleration * p_DeltaTime;
	m_Position += m_Velocity * p_DeltaTime;

	m_AngularVelocity += m_AngularAcceleration * p_DeltaTime;
	m_Rotation += m_AngularVelocity * p_DeltaTime;
}

void Kinematic::Update(float p_DeltaTime)
{
	integrate(p_DeltaTime);
	UpdateChild();
}