#include "Random.h"

//make the instance a nullptr intially
Random * Random::m_spInstance = nullptr;

Random::Random()
{
	srand(time(NULL));
}

Random::~Random()
{

}

Random * Random::instance()
{
	return m_spInstance;
}

int Random::getRandInt(int p_Min, int p_Max)
{
	int iRandNum = 
	return 0;
}

