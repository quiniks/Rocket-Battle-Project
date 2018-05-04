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
	static float dot(sf::Vector2f a, sf::Vector2f b);
	static sf::Vector2f cross(sf::Vector2f a, float scalar);
	static float cross(sf::Vector2f a, sf::Vector2f b);
	static float mag(sf::Vector2f a);
	static sf::Vector2f unit(sf::Vector2f a);
public:
	static void resolve(Particle & p_Particle, sf::Vector2f p_Normal, sf::Vector2i p_CollosionPos);
	static void resolve(DynamicObject & p_DynamicObj, sf::Vector2f p_Normal, float p_DeltaTime);
	static bool rayCast(sf::Vector2i p_Start, sf::Vector2i p_Target, Terrain& p_Terrain, sf::Vector2i& p_HitPos); //could move to terrain class
	//static bool OBBvsTerrain(sf::RectangleShape & p_StartBoundingBox, sf::RectangleShape & p_TargetBoundingBox, Terrain& p_Terrain, sf::Vector2i& p_CorrectionPos, sf::Vector2i& p_ContactVector, sf::Vector2i& p_ContactPos);
	static bool AABBvsTerrain(sf::FloatRect p_BB, sf::Vector2f p_Pos, Terrain& p_Terrain, sf::Vector2f& p_AverageUnitNormal);
};
