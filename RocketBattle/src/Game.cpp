#include "Game.h"

Game::Game(sf::RenderWindow& p_Window)
{
	m_View.setCenter(m_CameraSize.x / 2, m_CameraSize.y / 2);
	m_View.setSize(m_CameraSize.x, m_CameraSize.y);
	m_View.zoom(1);
	m_View.move(0.0f, 0.0f);
	p_Window.setView(m_View);

	m_ParticleSystem = new ParticleSystem(p_Window.getSize());

	m_TextureLoader = TextureLoader::instance();
	m_TextureLoader->loadTextures(".\\Assets\\Textures");
	m_Terrain.LoadTerrain(m_TextureLoader->getTexture("Grass.png"));

	sf::Vector2f l_Normal = m_Terrain.GetNormal(8, 8, 3);
	//std::cout << l_Normal.x << std::endl;
	//std::cout << l_Normal.y << std::endl;

	sf::CircleShape l_Circle;
	l_Circle.setRadius(50);
	l_Circle.setPosition(100, 300);
	l_Circle.setFillColor(sf::Color::Transparent);
	m_Terrain.SubtractShape(&l_Circle);
}

Game::~Game()
{
	
}

void Game::handleKeyboardInput(int key)
{
	//std::cout << key << std::endl;
	if (key == sf::Keyboard::Tab) {
			m_Debug = !m_Debug;
	}
}

void Game::handleMouseInput(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Left) {
		m_ParticleSystem->Explosion(m_MouseWorldPos, m_Gravity, 20.0f, 20, 15.0f, 0.2f);
	}
}

void Game::handleMouseMove(const sf::RenderWindow& p_Window)
{
	sf::Vector2i p_MousePixelPos = sf::Mouse::getPosition(p_Window);
	m_MouseWorldPos = p_Window.mapPixelToCoords(p_MousePixelPos);
}

void Game::update(float p_TimeStep)
{
	if (m_Debug) {
		std::cout << "particle count: " << m_ParticleSystem->size() << std::endl;
	}
	m_ParticleSystem->Update(p_TimeStep);
	for (int i = 0; i < m_ParticleSystem->size(); i++) {
		Particle& l_Particle = m_ParticleSystem->getParticle(i);
		if (!m_Terrain.isPixelEmpty((sf::Vector2u)l_Particle.getPosition())) {
			//dyn l_Particle has collided with terrain
			sf::Vector2i l_ColPos = CollisionHelper::rayCast((sf::Vector2i)l_Particle.getLastPos(), (sf::Vector2i)l_Particle.getPosition(), m_Terrain);
			sf::Vector2f l_Normal = m_Terrain.GetNormal(l_Particle.getPosition().x, l_Particle.getPosition().y, 3);
			//std::cout << l_Particle.getLastPos().x << "|" << l_Particle.getPosition().x << "|" << l_ColPos.x << std::endl;
			CollisionHelper::resolve(l_Particle, l_Normal, l_ColPos);
		}
	}
}

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_Terrain);
	target.draw(*m_ParticleSystem);
}

bool Game::getDebug()
{
	return m_Debug;
}
