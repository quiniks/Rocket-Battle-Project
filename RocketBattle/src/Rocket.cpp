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

	m_LifeBarOffset = sf::Vector2f(0.0f, -(p_Size.y/2.0f + 5.0f));
	m_LifeBar.setSize(sf::Vector2f(20.0f, 3.0f));
	m_LifeBarMaxLength = 20.0f;
	m_LifeBar.setOrigin(m_LifeBar.getSize().x / 2.0f, m_LifeBar.getSize().y / 2.0f);
	m_LifeBar.setPosition(p_StartPos + m_LifeBarOffset);
	m_LifeBar.setFillColor(sf::Color::Green);
	m_Life = m_MaxLife;

	m_FuelBarOffset = sf::Vector2f(0.0f, -(p_Size.y / 2.0f + 9.0f));
	m_FuelBar.setSize(sf::Vector2f(20.0f, 3.0f));
	m_FuelBarMaxLength = 20.0f;
	m_FuelBar.setOrigin(m_LifeBar.getSize().x / 2.0f, m_LifeBar.getSize().y / 2.0f);
	m_FuelBar.setPosition(p_StartPos + m_LifeBarOffset);
	m_FuelBar.setFillColor(sf::Color::Yellow);
	m_Fuel = m_MaxFuel;
}

Rocket::~Rocket()
{
}

void Rocket::setTexture(sf::Texture * p_Texture)
{
	m_Sprite.setTexture(*p_Texture);
}

void Rocket::setLife(float p_Life)
{
	m_Life = p_Life;
	sf::Vector2f l_NewSize = sf::Vector2f(m_LifeBarMaxLength * (p_Life / m_MaxLife), m_LifeBar.getSize().y);
	m_LifeBar.setSize(l_NewSize);
}

float Rocket::getLife()
{
	return m_Life;
}

void Rocket::setFuel(float p_Fuel)
{
	m_Fuel = p_Fuel;
	sf::Vector2f l_NewSize = sf::Vector2f(m_FuelBarMaxLength * (p_Fuel / m_MaxFuel), m_FuelBar.getSize().y);
	m_FuelBar.setSize(l_NewSize);
}

float Rocket::getFuel()
{
	return m_Fuel;
}

int Rocket::getTeam()
{
	return m_Team;
}

float Rocket::area()
{
	return (m_BoundingBox.width * m_BoundingBox.height);
}

void Rocket::update()
{
	m_LifeBar.setPosition(m_Position + m_LifeBarOffset);
	m_FuelBar.setPosition(m_Position + m_FuelBarOffset);

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
	target.draw(m_LifeBar);
	target.draw(m_FuelBar);
}
