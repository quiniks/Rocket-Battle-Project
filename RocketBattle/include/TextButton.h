#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class TextButton : public sf::Drawable {
private:
	sf::Font m_Font;
	sf::Text m_Text;
	sf::Color m_BaseColor;
	sf::Color m_OverColor;
public:
	TextButton(sf::Font p_Font, std::string p_String, float p_CharSize, sf::Color p_BaseColor, sf::Color p_OverColor);
	~TextButton();
	void setPosition(sf::Vector2f p_Position);
	void update(sf::Vector2f p_MousePos);
	bool isMouseOver(sf::Vector2f p_MousePos);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};