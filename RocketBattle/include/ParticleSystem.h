/*!
@file ParticleSystem.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "Particle.h"
#include <stdlib.h>
#include "Random.h"
#include "CollisionHelper.h"

/* \class ParticleSystem
\brief
*/

class ParticleSystem : public sf::Drawable {
private:
	std::vector<Particle> m_Particles;
	std::vector<sf::Vertex> m_Vertices;
	//testing
	sf::RenderTexture m_RenderTexture;
	sf::Sprite m_Sprite;
public:
	ParticleSystem(sf::Vector2u p_WindowSize);
	~ParticleSystem();
	void Explosion(sf::Vector2f p_Position, sf::Vector2f p_Acceleration, float p_MaxInitialSpeed, unsigned int p_Amount, float p_LifeTime, float p_Restitution);
	void Update(float p_DeltaTime);
	Particle& getParticle(unsigned int p_Index);
	unsigned int size();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};