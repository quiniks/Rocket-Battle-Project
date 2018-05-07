#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Scene.h"
#include "TextureLoader.h"
#include "TextButton.h"
#include "Menu.h"

class GameOver : public Scene {
private:
	sf::Font m_PixelFont;
	sf::Text m_Title;
	TextButton* m_MenuButton;
public:
	GameOver(sf::Vector2u p_WindowSize, std::string p_Winner, sf::Color p_Color);
	~GameOver();
	void handleKeyboardInput(int key);
	void handleMouseInput(sf::Mouse::Button button);
	void update(float p_TimeStep);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};