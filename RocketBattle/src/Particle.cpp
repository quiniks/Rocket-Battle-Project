#include "Particle.h"

Particle::Particle(float p_LifeTime, sf::Vector2f p_Accel, sf::Vector2f p_Vel, sf::Vector2f p_Pos, float p_Restitution, float p_Density, float p_DragCo)
{
	m_Density = p_Density;
	m_Position = p_Pos;
	m_Velocity = p_Vel;
	m_Acceleration = p_Accel;
	m_LifeTime = p_LifeTime;
	m_Restitution = p_Restitution;
	m_DragCoefficient = p_DragCo;
}

void Particle::setLastPos(sf::Vector2f p_Position)
{
	m_LastPosition = p_Position;
}

sf::Vector2f Particle::getLastPos()
{
	return m_LastPosition;
}

void Particle::setLife(float p_Time)
{
	m_LifeTime = p_Time;
}

float Particle::getLife()
{
	return m_LifeTime;
}

float Particle::area()
{
	return 1.0f;
}

void Particle::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}

void Particle::update()
{
	m_LastPosition = m_Position;
	float dragForceX = 0.5f * m_Density * (m_Velocity.x * abs(m_Velocity.x)) * m_DragCoefficient * area();
	float dragForceY = 0.5f * m_Density * (m_Velocity.y * abs(m_Velocity.y)) * m_DragCoefficient * area();
	applyForce(sf::Vector2f(-dragForceX, -dragForceY));
}

Particle::~Particle()
{
}