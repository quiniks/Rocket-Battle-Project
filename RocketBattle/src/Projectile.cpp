#include "..\include\Projectile.h"

Projectile::Projectile(sf::Texture * p_Texture, float p_Restitution, sf::Vector2f p_Size, sf::Vector2f p_StartPos, float p_Density, float p_DragCo, float p_FricCo, float p_Damage)
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

	m_Damage = p_Damage;
}

Projectile::~Projectile()
{

}

float Projectile::area()
{
	return m_BoundingBox.height * m_BoundingBox.width;
}

float Projectile::getDamage()
{
	return m_Damage;
}

void Projectile::update()
{
	m_Sprite.setPosition(m_Position);
}

void Projectile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}
