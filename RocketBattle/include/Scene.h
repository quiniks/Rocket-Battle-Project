#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

class Scene : public sf::Drawable {
protected:
	bool m_Debug = false;
	sf::View m_View;
	Scene* m_NextScene = nullptr;
	sf::Vector2u m_WindowSize;
	sf::Vector2f m_MouseWorldPos;
public:
	Scene();
	~Scene();
	virtual void handleKeyboardInput(int key) = 0;
	virtual void handleMouseInput(sf::Mouse::Button button) = 0;
	void handleMouseMove(const sf::RenderWindow& p_Window);
	virtual void update(float p_TimeStep) = 0;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
	Scene* getNextScene();
	bool isSceneFinished();
	bool getDebug();
};