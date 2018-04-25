/*!
@file Game.h
*/

#pragma once

#include "TextureLoader.h"
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>

class Game : public sf::Drawable {
private:
	
public:
	Game();
	~Game();
	void handleInput();
	void update(float p_TimeStep);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};