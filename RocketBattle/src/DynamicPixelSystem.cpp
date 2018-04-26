#include "DynamicPixelSystem.h"

DynamicPixelSystem::DynamicPixelSystem()
{
}

DynamicPixelSystem::~DynamicPixelSystem()
{
}

void DynamicPixelSystem::Explosion(sf::Vector2f p_Acceleration, sf::Vector2f p_Position, float p_InitialSpeed, unsigned int p_Amount, float p_LifeTime)
{
	p_LifeTime = std::abs(p_LifeTime);
	for (int i = 0; i < p_Amount; i++) {

		DynamicPixel pixel(p_LifeTime, p_Acceleration, );
		m_DynamicPixels.push_back();
	}
}

void DynamicPixelSystem::Update(float p_DeltaTime)
{
}

void DynamicPixelSystem::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}
