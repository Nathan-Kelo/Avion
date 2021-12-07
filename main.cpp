

#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <fstream>
#include <cmath>

#include "avion.h"

#include  "nlohmann/json.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

using json = nlohmann::json;


const sf::Vector2u WINDOW_SIZE(800, 600);
const sf::Vector2f PLANE_SIZE(100, 100);
const sf::Vector2f circle_vector(1, 1);

void doCircle(sf::RectangleShape& plane) {
	plane.move(circle_vector);
	plane.rotate(1);
}

int main() {
	/*
		//std::ifstream listavion("files/listavion.json");
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x,WINDOW_SIZE.y), "My window");
	window.setVerticalSyncEnabled(true);
	
	sf::Texture planetexture;
	sf::Texture backgroundtexture;
	sf::RectangleShape plane1(PLANE_SIZE);
	sf::RectangleShape background(sf::Vector2f(WINDOW_SIZE.x,WINDOW_SIZE.y));

	if (!planetexture.loadFromFile("files/airplane.png")) {
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
	

	background.setTexture(&backgroundtexture);
	
	plane1.setTexture(&planetexture);
	
	
	while (window.isOpen()) {
		sf::Event event;		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}

		window.clear(sf::Color::Black);
		window.draw(background);
		window.draw(plane1);
		doCircle(plane1);
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