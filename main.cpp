#include <iostream>
#include <ctime>
#include "avion.h"
#include  "nlohmann/json.hpp"
#include <fstream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using json = nlohmann::json;

int main() {
	const sf::Vector2u WINDOW_SIZE(800, 600);
	//std::ifstream listavion("files/listavion.json");
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x,WINDOW_SIZE.y), "My window");
	window.setVerticalSyncEnabled(true);
	
	sf::Texture planetexture;
	sf::Texture backgroundtexture;
	sf::Sprite plane1;
	sf::Sprite background;

	if (!planetexture.loadFromFile("files/airplane2.png")) {
		std::cerr << "Failed to load texture for planes" << std::endl;
		return EXIT_FAILURE;
	}
	if (!backgroundtexture.loadFromFile("files/fieldtexture.jpg")) {
		std::cerr << "Failed to load texture for background" << std::endl;
		return EXIT_FAILURE;
	}

	planetexture.setSmooth(true);
	backgroundtexture.setSmooth(true);
	backgroundtexture.isRepeated();
	

	background.setTexture(backgroundtexture);
	background.setScale(2., 2.);
	plane1.setTexture(planetexture);
	
	
	while (window.isOpen()) {
		sf::Event event;		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}

		window.clear(sf::Color::Black);
		window.draw(background);
		window.draw(plane1);
		window.display();
	}
	/*json avions;
	std::string myText;
	while (getline(listavion, myText)) {
		std::cout << myText;
	}

	try {
		avions = json::parse(listavion);
	}
	catch (json::parse_error& ex)
	{
		std::cerr << "Message : " << ex.what() << std::endl;
	}
	srand(time(NULL));
	
listavion.close();
*/
	return 0;
}