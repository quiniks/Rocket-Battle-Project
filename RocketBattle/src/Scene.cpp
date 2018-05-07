#include "..\include\Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
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