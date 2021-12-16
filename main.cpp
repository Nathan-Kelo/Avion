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

/*struct Aeroport {
	int x;
	int y;
};*/

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
		//window.draw(background);
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


	auto random_x = randomx(rng);
	auto random_y = randomy(rng);
	auto random_p = randomp(rng);


	//std::ifstream listavion("files/listavion.json");

	//génération aeroport

	std::cout << "test";
	
	Aeroport Lille(randomx(rng), randomy(rng), randomp(rng));
	Aeroport Paris(randomx(rng), randomy(rng), randomp(rng));
	Aeroport Lyon(randomx(rng), randomy(rng), randomp(rng));
	Aeroport Marseille(randomx(rng), randomy(rng), randomp(rng));
	Aeroport Bordeaux(randomx(rng), randomy(rng), randomp(rng));
	
	std::vector<Aeroport> nom_aeroport;

	nom_aeroport.push_back(std::move(Lille));
	nom_aeroport.push_back(std::move(Paris));
	nom_aeroport.push_back(std::move(Marseille));
	nom_aeroport.push_back(std::move(Lyon));
	nom_aeroport.push_back(std::move(Bordeaux));


	std::cout << "------valeurs coordS------";
	std::cout << Lille.get_coord_x() << std::endl;
	std::cout << Lille.get_coord_y() << std::endl;
	std::cout << Paris.get_coord_x() << std::endl;
	std::cout << Paris.get_coord_y() << std::endl;
	std::cout << "------valeurs coordS------";

	

	constexpr int base_speed = 5;
	std::vector<std::unique_ptr<Avion>> avions;

	/*ap1.x = 200;
	ap1.y = 200;
	ap2.x = 400;
	ap2.y = 400;*/
	sf::Texture planeTexture;
	if (!planeTexture.loadFromFile("files/airplane.png")) {
		std::cerr << "Failed to load texture for planes" << std::endl;
		return EXIT_FAILURE;
	}

	//Avion plane1;//NEED TO PUT IN ALL THE ARGS	

	avions.push_back(std::make_unique<Avion>(planeTexture, base_speed * 2, 25.f, Lille.get_coord_x(), Lille.get_coord_y(), Paris.get_coord_x(), Paris.get_coord_x()));
	avions.push_back(std::make_unique<Avion>(planeTexture, base_speed * 2, 25.f, Paris.get_coord_x(), Paris.get_coord_x(), Lille.get_coord_x(), Lille.get_coord_y()));
	
	std::thread UI(visualization, std::ref(avions));
	
	UI.join();

	
	return 0;
}