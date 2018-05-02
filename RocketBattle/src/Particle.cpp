#include "Particle.h"

Particle::Particle(float p_LifeTime, sf::Vector2f p_Accel, sf::Vector2f p_Vel, sf::Vector2f p_Pos, float p_Restitution)
{
	m_Position = p_Pos;
	m_Velocity = p_Vel;
	m_Acceleration = p_Accel;
	m_LifeTime = p_LifeTime;
	m_Restitution = p_Restitution;
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

void Particle::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}

void Particle::UpdateChild()
{
}

Particle::~Particle()
{
}