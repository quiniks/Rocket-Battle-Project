#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Scene.h"
#include "TextureLoader.h"
#include "TextButton.h"
#include "Game.h"

class Menu : public Scene {
private:
	sf::Font m_PixelFont;
	sf::Text m_Title;
	TextButton* m_StartButton;
	sf::Sprite m_Hint;
public:
	Menu(sf::Vector2u p_WindowSize);
	~Menu();
	void handleKeyboardInput(int key);
	void handleMouseInput(sf::Mouse::Button button);
	void update(float p_TimeStep);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};