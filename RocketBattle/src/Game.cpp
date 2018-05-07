#include "Game.h"

Game::Game(sf::Vector2u p_WindowSize)
{
	m_WindowSize = p_WindowSize;
	m_View.setCenter(p_WindowSize.x / 2, p_WindowSize.y / 2);
	m_View.setSize(p_WindowSize.x, p_WindowSize.y);
	m_View.zoom(1);

	m_ViewArea.setSize((sf::Vector2f)p_WindowSize);
	m_ViewArea.setFillColor(sf::Color::Transparent);
	m_ViewArea.setOutlineColor(sf::Color::White);
	m_ViewArea.setOutlineThickness(10.0f);
	m_ViewArea.setOrigin(m_ViewArea.getSize() / 2.0f);

	m_TextureLoader = TextureLoader::instance();

	m_PauseSprite.setTexture(*m_TextureLoader->getTexture("Paused.png"));
	m_PauseSprite.setOrigin(m_PauseSprite.getLocalBounds().width / 2.0f, m_PauseSprite.getLocalBounds().height / 2.0f);

	sf::Texture* m_Map = m_TextureLoader->getTexture("CubeMap.png");
	m_Terrain.loadTerrain(m_Map, m_TextureLoader->getTexture("CubeMapBack.png"));

	m_MiniView.setSize(m_Map->getSize().x, m_Map->getSize().y);
	m_MiniView.setCenter(m_Map->getSize().x / 2, m_Map->getSize().y / 2);
	sf::FloatRect l_MiniMapRect = sf::FloatRect(0.0f, 0.0f, 0.2f, 0.2f);
	m_MiniView.setViewport(l_MiniMapRect);

	
	m_Rockets.push_back(Rocket(m_TextureLoader->getTexture("RedRocket.png"), 0.3f, sf::Vector2f(30.0f, 35.0f),
		sf::Vector2f(286.0f, 50.0f), 10.0f, 0.01f, 0.5f, Teams::red));

	m_Rockets.push_back(Rocket(m_TextureLoader->getTexture("BlueRocket.png"), 0.3f, sf::Vector2f(30.0f, 35.0f),
		sf::Vector2f(700.0f, 190.0f), 10.0f, 0.01f, 0.5f, Teams::blue));

	m_Rockets.push_back(Rocket(m_TextureLoader->getTexture("RedRocket.png"), 0.3f, sf::Vector2f(30.0f, 35.0f),
		sf::Vector2f(1296.0f, 150.0f), 10.0f, 0.01f, 0.5f, Teams::red));

	m_Rockets.push_back(Rocket(m_TextureLoader->getTexture("BlueRocket.png"), 0.3f, sf::Vector2f(30.0f, 35.0f),
		sf::Vector2f(300.0f, 550.0f), 10.0f, 0.01f, 0.5f, Teams::blue));

	m_Rockets.push_back(Rocket(m_TextureLoader->getTexture("RedRocket.png"), 0.3f, sf::Vector2f(30.0f, 35.0f),
		sf::Vector2f(1050.0f, 550.0f), 10.0f, 0.01f, 0.5f, Teams::red));

	m_Rockets.push_back(Rocket(m_TextureLoader->getTexture("BlueRocket.png"), 0.3f, sf::Vector2f(30.0f, 35.0f),
		sf::Vector2f(1460.0f, 557.0f), 10.0f, 0.01f, 0.5f, Teams::blue));

	m_PlayerRocket = &m_Rockets.at(0);
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
	else if (key == sf::Keyboard::Escape) {
		if (m_State == State::running) {
			m_State = State::paused;
		}
		else if (m_State == State::paused) {
			m_State = State::running;
		}
	}
}

void Game::handleMouseInput(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Left) {
		if (m_State == State::running) {
			if (m_HasShot == false) {
				m_HasShot = true;
				m_Bullets.push_back(Projectile(m_TextureLoader->getTexture("Bullet.png"), 0.0f, sf::Vector2f(7.0f, 7.0f), m_PlayerRocket->getPosition(), 0.1f, 5.0f, 0.0f, 50.0f));
				sf::Vector2f l_InitialVel = m_AimLine.getMultiplier() * 100.0f * m_AimLine.getDirUnit();
				m_Bullets.back().setVelocity(l_InitialVel);
			}
		}
	}
}

void Game::handleInputPerUpdate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (m_Rockets.size() != 0) {
			if (m_PlayerRocket->getFuel() > 0.0f) {
				m_Moving = true;
				m_PlayerRocket->applyForce(sf::Vector2f(0.0f, -1000000.0f));
				m_PlayerRocket->setFuel(m_PlayerRocket->getFuel() - 0.3f);
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (m_Rockets.size() != 0) {
			if (m_PlayerRocket->getFuel() > 0.0f) {
				m_Moving = true;
				m_PlayerRocket->applyForce(sf::Vector2f(-1000000.0f, 0.0f));
				m_PlayerRocket->setFuel(m_PlayerRocket->getFuel() - 0.3f);
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (m_Rockets.size() != 0) {
			if (m_PlayerRocket->getFuel() > 0.0f) {
				m_Moving = true;
				m_PlayerRocket->applyForce(sf::Vector2f(0.0f, 1000000.0f));
				m_PlayerRocket->setFuel(m_PlayerRocket->getFuel() - 0.3f);
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (m_Rockets.size() != 0) {
			if (m_PlayerRocket->getFuel() > 0.0f) {
				m_Moving = true;
				m_PlayerRocket->applyForce(sf::Vector2f(1000000.0f, 0.0f));
				m_PlayerRocket->setFuel(m_PlayerRocket->getFuel() - 0.3f);
			}
		}
	}
}

void Game::passTurn()
{
	int l_PrevTeam;
	int l_CurrentTeam;
	bool l_GameOver = false;
	for (int i = 0; i < m_Rockets.size(); i++) {
		if (i > 0) {
			l_PrevTeam = m_Rockets.at(i-1).getTeam();
			l_CurrentTeam = m_Rockets.at(i).getTeam();
			if (l_PrevTeam != l_CurrentTeam) {
				l_GameOver = false;
				break;
			}
			else {
				l_GameOver = true;
			}
		}
	}
	if (m_Rockets.size() == 1) {
		l_GameOver = true;
	}
	else if (m_Rockets.size() == 0) {
		l_GameOver = true;
	}
	if (l_GameOver) {
		if (m_Rockets.size() == 0) {
			m_NextScene = new GameOver(m_WindowSize, "Draw!", sf::Color::Yellow);
		}
		else if (m_Rockets.at(0).getTeam() == Teams::red) {
			m_NextScene = new GameOver(m_WindowSize, "Red team won", sf::Color::Red);
		}
		else if (m_Rockets.at(0).getTeam() == Teams::blue) {
			m_NextScene = new GameOver(m_WindowSize, "Blue team won", sf::Color::Blue);
		}
	} else{
		if (m_TeamTurn == Teams::red) { //red to blue
			m_PlayerRocket->setTexture(m_TextureLoader->getTexture("RedRocket.png"));
			for (int i = m_RocketIndex; i < m_Rockets.size() + 1; i++) {
				if (i > m_Rockets.size() - 1) {
					i = 0;
				}
				if (m_Rockets.at(i).getTeam() == Teams::blue) {
					m_PlayerRocket = &m_Rockets.at(i);
					m_RocketIndex = i;
					m_TeamTurn = Teams::blue;
					break;
				}
				if (i == m_Rockets.size() - 1) {
					i = -1;
				}
			}
		}
		else if (m_TeamTurn == Teams::blue) { //blue to red
			m_PlayerRocket->setTexture(m_TextureLoader->getTexture("BlueRocket.png"));
			for (int i = m_RocketIndex; i < m_Rockets.size() + 1; i++) {
				if (i > m_Rockets.size() - 1) {
					i = 0;
				}
				if (m_Rockets.at(i).getTeam() == Teams::red) {
					m_PlayerRocket = &m_Rockets.at(i);
					m_RocketIndex = i;
					m_TeamTurn = Teams::red;
					break;
				}
				if (i == m_Rockets.size() - 1) {
					i = -1;
				}
			}
		}
	}
	m_HasShot = false;
}

void Game::update(float p_TimeStep)
{
	if (m_State == 0) {
		handleInputPerUpdate();
		if (!m_HasShot) {
			m_View.setCenter(m_PlayerRocket->getPosition());
			m_ViewArea.setPosition(m_PlayerRocket->getPosition());
			m_PauseSprite.setPosition(m_PlayerRocket->getPosition());
		}
		else {
			m_View.setCenter(m_Bullets.at(0).getPosition());
			m_ViewArea.setPosition(m_Bullets.at(0).getPosition());
			m_PauseSprite.setPosition(m_Bullets.at(0).getPosition());
		}

		if (m_Moving) {
			if (m_PlayerRocket->getTeam() == Teams::red) {
				m_PlayerRocket->setTexture(m_TextureLoader->getTexture("RedRocketThrust.png"));
			}
			else if (m_PlayerRocket->getTeam() == Teams::blue) {
				m_PlayerRocket->setTexture(m_TextureLoader->getTexture("BlueRocketThrust.png"));
			}
		}
		else {
			if (m_PlayerRocket->getTeam() == Teams::red) {
				m_PlayerRocket->setTexture(m_TextureLoader->getTexture("RedRocket.png"));
			}
			else if (m_PlayerRocket->getTeam() == Teams::blue) {
				m_PlayerRocket->setTexture(m_TextureLoader->getTexture("BlueRocket.png"));
			}
		}
		m_Moving = false;

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
				m_Terrain.subtractShape(l_Circle);

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
				passTurn();
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

				if (CollisionHelper::AABBvsAABB(l_Bullet.getBoundBox(), l_Bullet.getPosition(), l_Rocket.getBoundBox(), l_Rocket.getPosition()) && i != m_RocketIndex) {
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
					m_Terrain.subtractShape(l_Circle);

					passTurn();
					m_ParticleSystem.Explosion(l_Bullet.getPosition(), m_Gravity, 50.0f, 100, 20.0f, 0.3f, 2.0f, 0.001f);
					m_Bullets.erase(m_Bullets.begin() + j);
					j--;
				}
			}
		}
		for (int i = 0; i < m_ParticleSystem.size(); i++) {
			Particle& l_Particle = m_ParticleSystem.getParticle(i);
			if (!m_Terrain.isPixelEmpty((sf::Vector2i)l_Particle.getPosition())) {
				//dyn l_Particle has collided with terrain
				sf::Vector2i l_ColPos = sf::Vector2i(0, 0);
				bool l_Hit = CollisionHelper::rayCast((sf::Vector2i)l_Particle.getLastPos(), (sf::Vector2i)l_Particle.getPosition(), m_Terrain, l_ColPos);
				sf::Vector2f l_Normal = m_Terrain.getNormal(l_Particle.getPosition().x, l_Particle.getPosition().y, 3);
				CollisionHelper::resolve(l_Particle, l_Normal, l_ColPos);
			}
			l_Particle.applyAcceleration(m_Gravity);
		}
		m_ParticleSystem.Update(p_TimeStep);
	}
}

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//DRAW GAME
	target.setView(m_View);
	target.draw(m_Terrain);
	for (int i = 0; i < m_Bullets.size(); i++) {
		target.draw(m_Bullets.at(i));
	}
	target.draw(m_AimLine);
	for (int i = 0; i < m_Rockets.size(); i++) {
		target.draw(m_Rockets.at(i));
	}
	target.draw(m_ParticleSystem);
	if (m_State == State::paused) {
		target.draw(m_PauseSprite);
	}
	//DRAW MINI MAP
	target.setView(m_MiniView);
	target.draw(m_Terrain);
	for (int i = 0; i < m_Rockets.size(); i++) {
		target.draw(m_Rockets.at(i));
	}
	target.draw(m_ViewArea);
}
