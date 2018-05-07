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
	return m_SceneFinished;
}

bool Scene::getDebug()
{
	return m_Debug;
}