#include "..\include\DynamicSprite.h"

DynamicSprite::DynamicSprite(sf::Texture * p_Texture, float p_Restitution, sf::Vector2f p_Size, sf::Vector2f p_StartPos, float p_Density, float p_DragCo, float p_FricCo)
{
	m_Sprite.setTexture(*p_Texture);
	m_Sprite.setPosition(p_StartPos);

	m_Position = p_StartPos;
	m_Restitution = p_Restitution;
	m_BoundingBox = sf::FloatRect(p_StartPos, p_Size);
	m_Density = p_Density;
	m_Mass = area() * p_Density;
	m_DragCoefficient = p_DragCo;
	m_FrictionCoefficient = p_FricCo;
}

DynamicSprite::~DynamicSprite()
{

}

float DynamicSprite::area()
{
	return m_BoundingBox.height * m_BoundingBox.width;
}

void DynamicSprite::update()
{
	m_Sprite.setPosition(m_Position);
}

void DynamicSprite::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}
