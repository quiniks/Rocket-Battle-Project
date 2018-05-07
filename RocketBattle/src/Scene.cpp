#include "..\include\Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::handleMouseMove(const sf::RenderWindow & p_Window)
{
	sf::Vector2i p_MousePixelPos = sf::Mouse::getPosition(p_Window);
	m_MouseWorldPos = p_Window.mapPixelToCoords(p_MousePixelPos, m_View);
}

Scene* Scene::getNextScene()
{
	return m_NextScene;
}

bool Scene::isSceneFinished()
{
	if (m_NextScene != nullptr) {
		return true;
	}
	return false;
}

bool Scene::getDebug()
{
	return m_Debug;
}