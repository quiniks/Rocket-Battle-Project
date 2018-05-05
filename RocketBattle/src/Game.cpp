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
	m_Terrain.LoadTerrain(m_TextureLoader->getTexture("testmap2.png"), m_TextureLoader->getTexture("testmap2back.png"));
	
	m_Rockets.push_back(Rocket(m_TextureLoader->getTexture("RedRocket.png"), 0.5f, sf::Vector2f(30.0f, 35.0f),
								sf::Vector2f(200.0f, 100.0f), 10.0f, 0.1f, 0.5f, Teams::red));
	m_Rockets.push_back(Rocket(m_TextureLoader->getTexture("BlueRocket.png"), 0.5f, sf::Vector2f(30.0f, 35.0f),
								sf::Vector2f(500.0f, 100.0f), 10.0f, 0.1f, 0.5f, Teams::blue));
	m_PlayerRocket = &m_Rockets.at(m_Turn);
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
		m_Bullets.push_back(Projectile(m_TextureLoader->getTexture("Bullet.png"), 0.0f, sf::Vector2f(7.0f, 7.0f), m_PlayerRocket->getPosition(), 0.1f, 5.0f, 0.0f, 50.0f));
		sf::Vector2f l_InitialVel = m_AimLine.getMultiplier() * 200.0f * m_AimLine.getDirUnit();
		m_Bullets.back().setVelocity(l_InitialVel);
	}
}

void Game::handleMouseMove(const sf::RenderWindow& p_Window)
{
	sf::Vector2i p_MousePixelPos = sf::Mouse::getPosition(p_Window);
	m_MouseWorldPos = p_Window.mapPixelToCoords(p_MousePixelPos);
}

void Game::handleInputPerUpdate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (m_PlayerRocket->getFuel() > 0.0f) {
			m_PlayerRocket->applyForce(sf::Vector2f(0.0f, -1000000.0f));
			m_PlayerRocket->setFuel(m_PlayerRocket->getFuel() - 0.3f);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (m_PlayerRocket->getFuel() > 0.0f) {
			m_PlayerRocket->applyForce(sf::Vector2f(-1000000.0f, 0.0f));
			m_PlayerRocket->setFuel(m_PlayerRocket->getFuel() - 0.3f);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (m_PlayerRocket->getFuel() > 0.0f) {
			m_PlayerRocket->applyForce(sf::Vector2f(0.0f, 1000000.0f));
			m_PlayerRocket->setFuel(m_PlayerRocket->getFuel() - 0.3f);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (m_PlayerRocket->getFuel() > 0.0f) {
			m_PlayerRocket->applyForce(sf::Vector2f(1000000.0f, 0.0f));
			m_PlayerRocket->setFuel(m_PlayerRocket->getFuel() - 0.3f);
		}
	}
}

void Game::update(float p_TimeStep)
{
	handleInputPerUpdate();
	m_AimLine.update(m_MouseWorldPos, m_PlayerRocket->getPosition());

	if (m_Debug) {
		std::cout << "particle count: " << m_ParticleSystem.size() << std::endl;
	}
	for (int i = 0; i < m_Bullets.size(); i++) {
		Projectile& l_Bullet = m_Bullets.at(i);
		sf::Vector2f l_AverageUnitNormal = sf::Vector2f(0.0f, 0.0f);
		l_Bullet.applyAcceleration(m_Gravity);
		l_Bullet.polyUpdate(p_TimeStep);
		if (CollisionHelper::AABBvsTerrain(l_Bullet.getBoundBox(), l_Bullet.getPosition(), m_Terrain, l_AverageUnitNormal)) {

			sf::CircleShape l_Circle;
			l_Circle.setRadius(50);
			l_Circle.setPosition(l_Bullet.getPosition());
			l_Circle.setOrigin(sf::Vector2f(l_Circle.getRadius(), l_Circle.getRadius()));
			l_Circle.setFillColor(sf::Color::Transparent);
			m_Terrain.SubtractShape(l_Circle);

			for (int j = 0; j < m_Rockets.size(); j++) {
				Rocket& l_Rocket = m_Rockets.at(j);
				if (CollisionHelper::AABBvsCircle(l_Circle, l_Bullet.getPosition(), l_Rocket.getBoundBox(), l_Rocket.getPosition())) {
					l_Rocket.setLife(l_Rocket.getLife() - l_Bullet.getDamage());
					if (l_Rocket.getLife() <= 0.0f) {
						m_Rockets.erase(m_Rockets.begin() + j);
						j--;
					}
				}
			}

			m_ParticleSystem.Explosion(l_Bullet.getPosition(), m_Gravity, 50.0f, 100, 20.0f, 0.3f, 2.0f, 0.001f);
			m_Bullets.erase(m_Bullets.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < m_Rockets.size(); i++) {
		Rocket& l_Rocket = m_Rockets.at(i);
		sf::Vector2f l_AverageUnitNormal = sf::Vector2f(0.0f, 0.0f);
		l_Rocket.applyAcceleration(m_Gravity);
		l_Rocket.polyUpdate(p_TimeStep);
		if (CollisionHelper::AABBvsTerrain(l_Rocket.getBoundBox(), l_Rocket.getPosition(), m_Terrain, l_AverageUnitNormal)) {
			CollisionHelper::resolve(l_Rocket, l_AverageUnitNormal, p_TimeStep);
		}
		for (int j = 0; j < m_Bullets.size(); j++) {
			Projectile& l_Bullet = m_Bullets.at(j);
			
			if (CollisionHelper::AABBvsAABB(l_Bullet.getBoundBox(), l_Bullet.getPosition(), l_Rocket.getBoundBox(), l_Rocket.getPosition()) && i != m_Turn) {
				l_Rocket.setLife(l_Rocket.getLife() - l_Bullet.getDamage());
				if (l_Rocket.getLife() <= 0.0f) {
					m_Rockets.erase(m_Rockets.begin() + i);
					i--;
				}
				sf::CircleShape l_Circle;
				l_Circle.setRadius(50);
				l_Circle.setPosition(l_Bullet.getPosition());
				l_Circle.setOrigin(sf::Vector2f(l_Circle.getRadius(), l_Circle.getRadius()));
				l_Circle.setFillColor(sf::Color::Transparent);
				m_Terrain.SubtractShape(l_Circle);

				m_ParticleSystem.Explosion(l_Bullet.getPosition(), m_Gravity, 50.0f, 100, 20.0f, 0.3f, 2.0f, 0.001f);
				m_Bullets.erase(m_Bullets.begin() + j);
				j--;
			}
		}
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
	target.draw(m_AimLine);
	for (int i = 0; i < m_Rockets.size(); i++) {
		target.draw(m_Rockets.at(i));
	}
	for (int i = 0; i < m_Bullets.size(); i++) {
		target.draw(m_Bullets.at(i));
	}
	target.draw(m_ParticleSystem);
}

bool Game::getDebug()
{
	return m_Debug;
}
