/*!
@file CollisionHelper.h
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "DynamicObject.h"
#include "Terrain.h"
#include "Particle.h"
#include <iostream>

/* \class CollisionHelper
\brief A class that contains all the relavent collision checking and resolve methods
*/

class CollisionHelper {
private:
	CollisionHelper(); //!< private constructor
	~CollisionHelper(); //!< Destructor
	/*!
	* dot product of two vectors
	* @param[in] a Vector A
	* @param[in] a Vector B
	*/
	static float dot(sf::Vector2f a, sf::Vector2f b);
	/*!
	* cross product type 1 of vector and scalar
	* @param[in] a Vector A
	* @param[in] scalar Scalar value
	*/
	static sf::Vector2f cross(sf::Vector2f a, float scalar);
	/*!
	* cross product type 2 of vector and vector
	* @param[in] a Vector A
	* @param[in] b Vector B
	*/
	static float cross(sf::Vector2f a, sf::Vector2f b);
	/*!
	* magnitude of a vector
	* @param[in] a Vector A
	*/
	static float mag(sf::Vector2f a);
	/*!
	* unit vector of a vector
	* @param[in] a Vector A
	*/
	static sf::Vector2f unit(sf::Vector2f a);
public:
	/*!
	* resolve a particle collision
	* @param[in] p_Particle The particle that collided
	* @param[in] p_Normal the surface normal
	* @param[in] p_CollisionPos the point of impact
	*/
	static void resolve(Particle & p_Particle, sf::Vector2f p_Normal, sf::Vector2i p_CollosionPos);
	/*!
	* resolve a dynamic object collision
	* @param[in] p_DynamicObj The dynamic object that collided
	* @param[in] p_Normal The surface normal
	* @param[in] p_DeltaTime The time elapsed since last frame
	*/
	static void resolve(DynamicObject & p_DynamicObj, sf::Vector2f p_Normal, float p_DeltaTime);
	/*!
	* Iterate from point a to b and return true if the ray hits the terrain
	* @param[in] p_Start Tay start position
	* @param[in] p_Target Tay target position
	* @param[in] p_Terrain The terrain
	* @param[out] p_HitPos the point at which the ray hits the terrain
	*/
	static bool rayCast(sf::Vector2i p_Start, sf::Vector2i p_Target, Terrain& p_Terrain, sf::Vector2i& p_HitPos); //could move to terrain class
	//static bool OBBvsTerrain(sf::RectangleShape & p_StartBoundingBox, sf::RectangleShape & p_TargetBoundingBox, Terrain& p_Terrain, sf::Vector2i& p_CorrectionPos, sf::Vector2i& p_ContactVector, sf::Vector2i& p_ContactPos);
	/*!
	* Axis Aligned Bounding Box vs Terrain collision check
	* @param[in] p_BB Bounding box
	* @param[in] p_Pos Position of Bounding Box
	* @param[in] p_Terrain The terrain
	* @param[out] p_AverageUnitNormal the average unit surface normal of edge points of the bounding box inside the terrain
	*/
	static bool AABBvsTerrain(sf::FloatRect p_BB, sf::Vector2f p_Pos, Terrain& p_Terrain, sf::Vector2f& p_AverageUnitNormal);
	/*!
	* Axis Aligned Bounding Box vs Axis Aligned Bounding Box collision check
	* @param[in] p_BB1 Bounding box 1
	* @param[in] p_Pos1 Position of Bounding Box 1
	* @param[in] p_BB2 Bounding box 2
	* @param[int] p_Pos2 Position of Bounding Box 2
	*/
	static bool AABBvsAABB(sf::FloatRect p_BB1, sf::Vector2f p_Pos1, sf::FloatRect p_BB2, sf::Vector2f p_Pos2);
	/*!
	* Axis Aligned Bounding Box vs Circle collision check
	* @param[in] p_Circle Circle 1
	* @param[in] p_Pos1 Position of Circle 1
	* @param[in] p_BB2 Bounding box 2
	* @param[int] p_Pos2 Position of Bounding Box 2
	*/
	static bool AABBvsCircle(sf::CircleShape p_Circle1, sf::Vector2f p_Pos1, sf::FloatRect p_BB2, sf::Vector2f p_Pos2);
};
