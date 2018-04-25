#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Rocket Lander Project");
	Game game;

	sf::Clock clock;
	const unsigned int fps = 60;
	const float timeStep = 1.0f / fps;
	float accumulatedTime = 0.0f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:

				break;
			}
			// window closed button pressed
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		float elapsedTime = clock.restart().asSeconds();
		if (elapsedTime > 0.25f) {
			elapsedTime = 0.25f;
		}
		accumulatedTime += elapsedTime;
		while (accumulatedTime >= timeStep) {
			//update
			game.update(timeStep);
			accumulatedTime -= timeStep;
		}
		//render
		window.clear(sf::Color::Black);
		window.draw(game);
		window.display();
	}

	//system("pause");
	return EXIT_SUCCESS;
}