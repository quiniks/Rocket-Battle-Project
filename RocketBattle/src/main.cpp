#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Rocket Battle Project");

	Game game(window);

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
				game.handleKeyboardInput(event.key.code);
				break;
			case sf::Event::MouseButtonPressed:
				game.handleMouseInput(event.mouseButton.button);
				break;
			case sf::Event::MouseMoved:
				game.handleMouseMove(window);
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
			if (game.getDebug()) {
				std::cout << "--------------" << std::endl << "render fps: " << 1.0f / elapsedTime << std::endl;
				std::cout << "physics fps: " << 1.0f / accumulatedTime << std::endl;
			}
			game.update(timeStep);
			accumulatedTime -= timeStep;
		}
		//render
		window.clear(sf::Color::Blue);
		window.draw(game);
		window.display();
		//system("cls");
	}
	//system("pause");
	return EXIT_SUCCESS;
}