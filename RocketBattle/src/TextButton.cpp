#include "..\include\TextButton.h"

TextButton::TextButton(sf::Font p_Font, std::string p_String, float p_CharSize, sf::Color p_BaseColor, sf::Color p_OverColor)
{
	m_Font = p_Font;
	m_Text.setFont(m_Font);
	m_Text.setString(p_String);
	m_Text.setCharacterSize(p_CharSize);
	m_Text.setFillColor(sf::Color::White);
	m_Text.setOrigin(m_Text.getLocalBounds().width / 2.0f, m_Text.getLocalBounds().height / 2.0f);
	m_BaseColor = p_BaseColor;
	m_OverColor = p_OverColor;
}

TextButton::~TextButton()
{
}

void TextButton::setPosition(sf::Vector2f p_Position)
{
	m_Text.setPosition(p_Position);
}

void TextButton::update(sf::Vector2f p_MousePos)
{
	if (m_Text.getGlobalBounds().contains(p_MousePos)) {
		m_Text.setFillColor(m_OverColor);
	}
	else {
		m_Text.setFillColor(m_BaseColor);
	}
}

bool TextButton::isMouseOver(sf::Vector2f p_MousePos)
{
	if (m_Text.getGlobalBounds().contains(p_MousePos)) {
		return true;
	}
	return false;
}

void TextButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_Text);
}
