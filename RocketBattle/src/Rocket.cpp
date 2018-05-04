#include "..\include\Rocket.h"

Rocket::Rocket(sf::Texture* p_Texture, float p_Restitution, sf::Vector2f p_Size, sf::Vector2f p_StartPos, float p_Density, float p_DragCo, float p_FricCo, int p_Team)
{
	m_Sprite.setTexture(*p_Texture);
	m_Sprite.setOrigin(p_Texture->getSize().x / 2, p_Texture->getSize().y / 2);
	m_Sprite.setPosition(p_StartPos);

	m_Position = p_StartPos;
	m_BoundingBox = sf::FloatRect(p_StartPos, p_Size);
	m_Team = p_Team;
	m_Density = p_Density;
	m_Restitution = p_Restitution;
	m_DragCoefficient = p_DragCo;
	m_FrictionCoefficient = p_FricCo;
	m_Mass = area() * m_Density;
}

Rocket::~Rocket()
{
}

void Rocket::setTexture(sf::Texture * p_Texture)
{
	m_Sprite.setTexture(*p_Texture);
}

float Rocket::area()
{
	return (m_BoundingBox.width * m_BoundingBox.height);
}

void Rocket::update()
{
	m_Sprite.setRotation(m_Rotation);
	m_Sprite.setPosition(m_Position);
	//Simple drag. Could be replace with drag that is relative to faces
	float dragForceX = 0.5f * m_Density * (m_Velocity.x * abs(m_Velocity.x)) * m_DragCoefficient * area();
	float dragForceY = 0.5f * m_Density * (m_Velocity.y * abs(m_Velocity.y)) * m_DragCoefficient * area();
	applyForce(sf::Vector2f(-dragForceX, -dragForceY));

	
}

void Rocket::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}
