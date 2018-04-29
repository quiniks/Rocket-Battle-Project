#pragma once

#include <SFML/Graphics.hpp>
#include "DynamicObject.h"
#include "Terrain.h"
#include "Particle.h"
#include <iostream>

class CollisionHelper {
private:
	CollisionHelper();
	~CollisionHelper();
public:
	static void resolve(DynamicObject& p_rDynamicObject, sf::Vector2f p_Normal, sf::Vector2i p_CollosionPos);
	static sf::Vector2i rayCast(sf::Vector2i p_Start, sf::Vector2i p_Target, Terrain& p_rTerrain); //could move to terrain class
};
