#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <fstream>
#include <cmath>
#include <vector>
#include <memory>
#include <string>
#include "avion.h"
#include "aeroport.h"
#include <random>

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

void visualization(std::vector<std::unique_ptr<Avion>>& avions, std::vector < std::unique_ptr<Aeroport>>& airports) {
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
		//window.draw(background);

		for (auto& airports : airports) {
			window.draw(airports->getSprite());
		}

		//window.draw(airports[4].getSprite());
		//window.draw(airports[1].getSprite());

		for (auto& avions : avions) {
			window.draw(avions->update_sprite());
		}
		window.display();
	}

}

int main() {

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> randomx(50, 550); // guaranteed unbiased
	std::uniform_int_distribution<int> randomy(50, 750); // guaranteed unbiased
	std::uniform_int_distribution<int> randomp(2, 15); // guaranteed unbiased

	//génération aeroport

	sf::Texture airporttexture;
	if (!airporttexture.loadFromFile("files/airport.png")) {
		std::cerr << "Failed to load texture for airport" << std::endl;
		return -1;
	}
	
	Aeroport Lille(airporttexture, 150, 150, randomp(rng));
	Aeroport Paris(airporttexture, 350, 350, randomp(rng));
	Aeroport Lyon(airporttexture, randomx(rng), randomy(rng), randomp(rng));
	Aeroport Marseille(airporttexture, randomx(rng), randomy(rng), randomp(rng));
	Aeroport Bordeaux(airporttexture, randomx(rng), randomy(rng), randomp(rng));
	
	std::vector<std::unique_ptr<Aeroport>> airports;

	/*airports.push_back(std::move(Lille));
	airports.push_back(std::move(Paris));
	airports.push_back(std::move(Marseille));
	airports.push_back(std::move(Lyon));
	airports.push_back(std::move(Bordeaux));*/

	airports.push_back(std::make_unique <Aeroport>(airporttexture, 150, 150, randomp(rng)));
	airports.push_back(std::make_unique<Aeroport>(airporttexture, 100, 100, 10));


	std::cout << "------valeurs coordS------";
	std::cout << Lille.get_coord_x() << std::endl;
	std::cout << Lille.get_coord_y() << std::endl;
	std::cout << Paris.get_coord_x() << std::endl;
	std::cout << Paris.get_coord_y() << std::endl;
	std::cout << "------valeurs coordS------";

	

	constexpr int base_speed = 5;
	std::vector<std::unique_ptr<Avion>> avions;

	sf::Texture planeTexture;
	if (!planeTexture.loadFromFile("files/airplane.png")) {
		std::cerr << "Failed to load texture for planes" << std::endl;
		return EXIT_FAILURE;
	}

	//Avion plane1;//NEED TO PUT IN ALL THE ARGS	

	avions.push_back(std::make_unique<Avion>(planeTexture, base_speed * 2, 25.f, airports[0]->get_coord_x(), airports[0]->get_coord_y(), airports[1]->get_coord_x(), airports[1]->get_coord_y()));
	avions.push_back(std::make_unique<Avion>(planeTexture, base_speed * 2, 25.f, airports[1]->get_coord_x(), airports[1]->get_coord_y(), airports[0]->get_coord_x(), airports[0]->get_coord_y()));


	std::thread UI(visualization, std::ref(avions), std::ref(airports));
	UI.join();

	
	return 0;
}