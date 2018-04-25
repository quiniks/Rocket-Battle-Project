#include "Game.h"

Game::Game()
{
	m_TextureLoader = TextureLoader::instance();
	m_TextureLoader->loadTextures(".\\Assets\\Textures");
	m_Terrain.LoadTerrain(m_TextureLoader->getTexture("test2.png"));

	sf::Vector2f l_Normal = m_Terrain.GetNormal(8, 8, 3);
	std::cout << l_Normal.x << std::endl;
	std::cout << l_Normal.y << std::endl;

	sf::CircleShape l_Circle;
	l_Circle.setRadius(50);
	l_Circle.setPosition(100, 300);
	l_Circle.setFillColor(sf::Color::Transparent);
	m_Terrain.SubtractShape(&l_Circle);
}

Game::~Game()
{
	
}

void Game::handleInput()
{
}

void Game::update(float p_TimeStep)
{
	
}

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.setView(m_View);
	target.draw(m_Terrain);
}
