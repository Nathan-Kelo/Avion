#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <fstream>
#include <cmath>
#include <vector>
#include <memory>

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

struct Aeroport {
	int x;
	int y;
};

void visualization(std::vector<std::unique_ptr<Avion>>& avions) {
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "My window");
	window.setVerticalSyncEnabled(true);

	sf::Texture backgroundtexture;
	if (!backgroundtexture.loadFromFile("files/fieldtexture.jpg")) {
		std::cerr << "Failed to load texture for background" << std::endl;
		return;
	}
	sf::RectangleShape background(sf::Vector2f(WINDOW_SIZE.x, WINDOW_SIZE.y));
	background.setTexture(&backgroundtexture);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}
		window.clear();
		window.draw(background);
		for (auto& avions : avions) {
			window.draw(avions->update_sprite());
			//std::cout << "We moved a plane" << std::endl;
		}
		window.display();
	}

}



int main() {
	//std::ifstream listavion("files/listavion.json");

	constexpr int base_speed = 5;
	std::vector<std::unique_ptr<Avion>> avions;
	Aeroport ap1;
	Aeroport ap2;

	ap1.x = 200;
	ap1.y = 200;
	ap2.x = 400;
	ap2.y = 400;
	sf::Texture planeTexture;
	if (!planeTexture.loadFromFile("files/airplane.png")) {
		std::cerr << "Failed to load texture for planes" << std::endl;
		return EXIT_FAILURE;
	}

	//Avion plane1;//NEED TO PUT IN ALL THE ARGS	
	
	avions.push_back(std::make_unique<Avion>(planeTexture, base_speed * 2, ap1.x, ap1.y, ap2.x, ap2.y));

	std::thread UI(visualization, std::ref(avions));

	UI.join();
																		   
	/*
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x,WINDOW_SIZE.y), "My window");
	window.setVerticalSyncEnabled(true);
	
	sf::Texture planetexture;
	sf::Texture backgroundtexture;
	
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
	Avion plane1(planetexture,base_speed*2,ap1.x,ap1.y,ap2.x,ap2.y);//NEED TO PUT IN ALL THE ARGS	
	
	
	while (window.isOpen()) {
		sf::Event event;		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}

		window.clear(sf::Color::Black);
		window.draw(background);
		
		
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