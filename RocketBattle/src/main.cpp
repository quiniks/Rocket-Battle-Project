#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"
#include "TextureLoader.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Rocket Battle Project");
	sf::RenderTexture l_RenderTex;
	l_RenderTex.create(window.getSize().x, window.getSize().y);
	sf::Sprite l_Canvas;

	TextureLoader* l_TextureLoader = TextureLoader::instance();
	l_TextureLoader->loadTextures(".\\Assets\\Textures");


	Scene* l_CurrentScene;
	l_CurrentScene = new Menu(window);

	sf::Clock clock;
	const unsigned int fps = 60;
	const float timeStep = 1.0f / fps;
	float accumulatedTime = 0.0f;

	while (window.isOpen())
	{
		if (l_CurrentScene->isSceneFinished()) {
			Scene* l_NextScene = l_CurrentScene->getNextScene();
			delete l_CurrentScene;
			l_CurrentScene = l_NextScene;
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				l_CurrentScene->handleKeyboardInput(event.key.code);
				break;
			case sf::Event::MouseButtonPressed:
				l_CurrentScene->handleMouseInput(event.mouseButton.button);
				break;
			default:
				break;
			}
		}

		float elapsedTime = clock.restart().asSeconds();
		
		if (elapsedTime > 0.25f) {
			elapsedTime = 0.25f;
		}
		
		accumulatedTime += elapsedTime;
		//std::cout << accumulatedTime << " | " << timeStep << std::endl;
		while (accumulatedTime >= timeStep) {
			//update
			if (l_CurrentScene->getDebug()) {
				std::cout << "--------------" << std::endl << "render fps: " << 1.0f / elapsedTime << std::endl;
				std::cout << "physics fps: " << 1.0f / accumulatedTime << std::endl;
			}
			l_CurrentScene->handleMouseMove(window);
			l_CurrentScene->update(timeStep);
			accumulatedTime -= timeStep;
		}
		//render
		window.clear(sf::Color::Black);
		l_RenderTex.clear(sf::Color::Transparent);
		l_RenderTex.draw(*l_CurrentScene);
		l_RenderTex.display();
		const sf::Texture& texture = l_RenderTex.getTexture();
		l_Canvas.setTexture(texture);
		window.draw(l_Canvas);
		window.display();
	}
	delete l_CurrentScene;
	l_CurrentScene = nullptr;
	//system("pause");
	return EXIT_SUCCESS;
}