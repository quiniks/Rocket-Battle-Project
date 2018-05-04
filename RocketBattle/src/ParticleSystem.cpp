#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::Explosion(sf::Vector2f p_Position, sf::Vector2f p_Acceleration, float p_MaxInitialSpeed, unsigned int p_Amount, float p_LifeTime, float p_Restitution, float p_Density, float p_DragCo)
{
	p_LifeTime = abs(p_LifeTime);
	Random* l_Random = Random::instance();
	
	for (unsigned int i = 0; i < p_Amount; i++) {
		float l_Radians = l_Random->getRand(0.0f, 1.0f) * 3.141592f * 2.0f;
		sf::Vector2f l_Dir = sf::Vector2f(cos(l_Radians), sin(l_Radians));
		sf::Vector2f l_Vel = l_Dir * l_Random->getRand(0.0f, p_MaxInitialSpeed);
		Particle l_Particle(p_LifeTime, p_Acceleration, l_Vel, p_Position, p_Restitution, p_Density, p_DragCo);
		m_Particles.push_back(l_Particle);
		m_Vertices.push_back(sf::Vertex(p_Position, sf::Color::Green));
	}
}

void ParticleSystem::Update(float p_DeltaTime)
{
	for (int i = 0; i < m_Particles.size(); i++) {
		Particle& l_Particle = m_Particles.at(i);
		//l_Particle.setLastPos(l_Particle.getPosition());
		l_Particle.polyUpdate(p_DeltaTime);
		m_Vertices[i].position = l_Particle.getPosition();

		if (l_Particle.getLife() > 0) {
			l_Particle.setLife(l_Particle.getLife() - p_DeltaTime);
		}
		else {
			m_Particles.erase(m_Particles.begin() + i);
			m_Vertices.erase(m_Vertices.begin() + i);
			i = i - 1;
		}
	}
}

Particle& ParticleSystem::getParticle(unsigned int p_Index)
{
	return m_Particles.at(p_Index);
}

unsigned int ParticleSystem::size()
{
	return m_Particles.size();
}

void ParticleSystem::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_Vertices.size() != 0) {
		target.draw(&m_Vertices[0], m_Vertices.size(), sf::Points, states);
	}
}
