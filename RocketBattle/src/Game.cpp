#include "Game.h"

Game::Game(sf::RenderWindow& p_Window)
{
	m_View.setCenter(m_CameraSize.x / 2, m_CameraSize.y / 2);
	m_View.setSize(m_CameraSize.x, m_CameraSize.y);
	m_View.zoom(1);
	m_View.move(0.0f, 0.0f);
	p_Window.setView(m_View);

	m_TextureLoader = TextureLoader::instance();
	m_TextureLoader->loadTextures(".\\Assets\\Textures");
	m_Terrain.LoadTerrain(m_TextureLoader->getTexture("testmap2.png"));

	sf::CircleShape l_Circle;
	l_Circle.setRadius(50);
	l_Circle.setPosition(100, 300);
	l_Circle.setFillColor(sf::Color::Transparent);
	m_Terrain.SubtractShape(l_Circle);
	m_Rockets.push_back(Rocket(m_TextureLoader->getTexture("RedRocket.png"), 0.5f, sf::Vector2f(30.0f, 35.0f),
								sf::Vector2f(200.0f, 100.0f), 10.0f, 0.001f, 0.5f, m_Teams::red));
	m_Rockets.push_back(Rocket(m_TextureLoader->getTexture("BlueRocket.png"), 0.2f, sf::Vector2f(30.0f, 35.0f),
								sf::Vector2f(500.0f, 100.0f), 10.0f, 0.001f, 0.5f, m_Teams::blue));
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
		m_ParticleSystem.Explosion(m_MouseWorldPos, m_Gravity, 20.0f, 500, 20.0f, 0.3f, 2.0f, 0.1f);
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
		std::cout << "particle count: " << m_ParticleSystem.size() << std::endl;
	}
	for (int i = 0; i < m_Rockets.size(); i++) {
		Rocket& l_Rocket = m_Rockets.at(i);
		//sf::Vector2i l_ContactVector = sf::Vector2i(0, 0);
		//sf::Vector2i l_CorrectionPos = sf::Vector2i(0, 0);
		sf::Vector2f l_AverageUnitNormal = sf::Vector2f(0.0f, 0.0f);
		if (CollisionHelper::AABBvsTerrain(l_Rocket.getBoundBox(), l_Rocket.getPosition(), m_Terrain, l_AverageUnitNormal)) {
			CollisionHelper::resolve(l_Rocket, l_AverageUnitNormal, p_TimeStep);
		}
		l_Rocket.applyAcceleration(m_Gravity);
		l_Rocket.polyUpdate(p_TimeStep);
	}
	for (int i = 0; i < m_ParticleSystem.size(); i++) {
		Particle& l_Particle = m_ParticleSystem.getParticle(i);
		if (!m_Terrain.isPixelEmpty((sf::Vector2u)l_Particle.getPosition())) {
			//dyn l_Particle has collided with terrain
			sf::Vector2i l_ColPos = sf::Vector2i(0, 0);
			bool l_Hit = CollisionHelper::rayCast((sf::Vector2i)l_Particle.getLastPos(), (sf::Vector2i)l_Particle.getPosition(), m_Terrain, l_ColPos);
			sf::Vector2f l_Normal = m_Terrain.GetNormal(l_Particle.getPosition().x, l_Particle.getPosition().y, 3);
			CollisionHelper::resolve(l_Particle, l_Normal, l_ColPos);
		}
		l_Particle.applyAcceleration(m_Gravity);
	}
	m_ParticleSystem.Update(p_TimeStep);
}

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_Terrain);
	for (int i = 0; i < m_Rockets.size(); i++) {
		target.draw(m_Rockets.at(i));
	}
	target.draw(m_ParticleSystem);
}

bool Game::getDebug()
{
	return m_Debug;
}
