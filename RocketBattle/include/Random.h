/*!
@file Random.h
*/

#pragma once

#include <iostream>
#include <random>

/* \class Random
\brief 
*/

class Random {
private:
	Random();	//!< Private constructor
	static Random * m_spInstance;	//!< Static pointer to the singleton texture loader
	std::mt19937 m_MT;
	~Random();	//!< Private destructor
public:
	static Random * instance();	//!< Returns a pointer to the static texture loader
	float getRand(float p_Min, float p_Max);
	Random(Random const&) = delete; //!< prevents the creation of multiple texture loaders
	Random& operator=(Random const&) = delete; //!< prevents the creation of multiple texture loaders
};