#include "..\include\Rocket.h"

Rocket::Rocket(sf::Texture* p_Texture, float p_Restitution, sf::Vector2f p_Size, sf::Vector2f p_StartPos, float p_Oriention)
{
	m_Sprite.setTexture(*p_Texture);
	m_Sprite.setOrigin(p_Texture->getSize().x / 2, p_Texture->getSize().y / 2);

	m_BoundingBox.setSize(p_Size);
	m_BoundingBox.setOrigin(p_Size.x / 2, p_Size.y / 2);
}

Rocket::~Rocket()
{
}

void Rocket::setTexture(sf::Texture * p_Texture)
{
	m_Sprite.setTexture(*p_Texture);
}

void Rocket::UpdateChild()
{
	m_BoundingBox.setRotation(m_Rotation);
	m_BoundingBox.setPosition(m_Position);

	m_Sprite.setRotation(m_Rotation);
	m_Sprite.setPosition(m_Position);
}

void Rocket::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}
