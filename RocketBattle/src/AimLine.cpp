#include "..\include\AimLine.h"

AimLine::AimLine()
{
	m_Vertices = sf::VertexArray(sf::Lines, 2);
	m_Vertices[0].color = sf::Color::White;
	m_Vertices[1].color = sf::Color::White;
}

AimLine::~AimLine()
{
}

float AimLine::getMultiplier()
{
	return m_Multiplier;
}

sf::Vector2f AimLine::getDirUnit()
{
	return m_DirUnitVector;
}

void AimLine::update(sf::Vector2f p_Target, sf::Vector2f p_Start)
{
	sf::Vector2f l_AimVector = p_Target - p_Start;
	float l_Mag = sqrtf(l_AimVector.x * l_AimVector.x + l_AimVector.y * l_AimVector.y);
	m_DirUnitVector = l_AimVector / l_Mag;
	sf::Vector2f l_OffsetStartVector = m_DirUnitVector * m_StartRadius;
	sf::Vector2f l_OffsetStartPos = p_Start + l_OffsetStartVector;
	m_Vertices[0].position = l_OffsetStartPos;

	sf::Vector2f l_OffsetAimVector = p_Target - l_OffsetStartPos;
	l_Mag = sqrtf(l_OffsetAimVector.x * l_OffsetAimVector.x + l_OffsetAimVector.y * l_OffsetAimVector.y);
	sf::Vector2f l_OffsetTargetVector;
	
	if (l_Mag <= m_MaxMag) {
		l_OffsetTargetVector = m_DirUnitVector * l_Mag;
		m_Multiplier = l_Mag / m_MaxMag;
	}
	else {
		l_OffsetTargetVector = m_DirUnitVector * m_MaxMag;
		m_Multiplier = 1.0f;
	}
	sf::Vector2f l_OffsetTargetPos = l_OffsetStartPos + l_OffsetTargetVector;;
	m_Vertices[1].position = l_OffsetTargetPos;
}

void AimLine::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_Vertices);
}
