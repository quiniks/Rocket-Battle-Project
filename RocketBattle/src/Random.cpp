#include "Random.h"

//make the instance a nullptr intially
Random * Random::m_spInstance = nullptr;

Random::Random()
{
	std::random_device rd;
	m_MT = std::mt19937(rd());
}

Random::~Random()
{
	delete m_spInstance;
	m_spInstance = nullptr;
}

Random * Random::instance()
{
	if (m_spInstance == nullptr) {
		m_spInstance = new Random();
	}
	return m_spInstance;
}

float Random::getRand(float p_Min, float p_Max)
{
	std::uniform_real_distribution<float> l_UniformDistrib(p_Min, p_Max);
	return l_UniformDistrib(m_MT);
}

