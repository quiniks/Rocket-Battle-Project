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
\brief A class that handles updating particles and drawing their respective vertices
*/

class ParticleSystem : public sf::Drawable {
private:
	std::vector<Particle> m_Particles; //!< Vector of dynamic particles
	std::vector<sf::Vertex> m_Vertices; //!< Vector of vertices
public:
	ParticleSystem(); //!< Default constructor
	~ParticleSystem();  //!< Destructor
	/*!
	* Creates an explosions of particles
	* @param[in] p_Position Initial Position
	* @param[in] p_Acceleration Intial Acceleration
	* @param[in] p_MaxInitialSpeed Maximum possible speed of a particle
	* @param[in] p_Amount Amount of particles to spawn
	* @param[in] p_LifeTime Time before a particle despawns
	* @param[in] p_Restitution Initial restitution
	* @param[in] p_Density Initial density
	* @param[in] p_DragCo Initial drag coefficient
	*/
	void Explosion(sf::Vector2f p_Position, sf::Vector2f p_Acceleration, float p_MaxInitialSpeed, unsigned int p_Amount, float p_LifeTime, float p_Restitution, float p_Density, float p_DragCo);
	/*!
	* Update the particles and vertex positions
	* @param[in] p_DeltaTime time elapsed since last frame
	*/
	void Update(float p_DeltaTime);
	/*!
	* returns a reference to a particle
	* @param[in] p_Index The index of the particle you want to get
	*/
	Particle& getParticle(unsigned int p_Index);
	unsigned int size(); //!< returns the amount of particles
	/*!
	* Draw
	* @param[in, out] target Render target to draw to
	* @param[in] states Render state
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};