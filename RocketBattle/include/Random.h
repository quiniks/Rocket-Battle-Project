/*!
@file Random.h
*/

#pragma once

#include <iostream>
#include <time.h>
#include <stdlib.h>

/* \class Random
\brief 
*/

class Random {
private:
	Random();	//!< Private constructor
	static Random * m_spInstance;	//!< Static pointer to the singleton texture loader
	~Random();	//!< Private destructor
public:
	static Random * instance();	//!< Returns a pointer to the static texture loader
	int getRandInt(int p_Min, int p_Max);
	Random(Random const&) = delete; //!< prevents the creation of multiple texture loaders
	Random& operator=(Random const&) = delete; //!< prevents the creation of multiple texture loaders
};