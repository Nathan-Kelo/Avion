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

Aeroport random(std::vector <Aeroport> airports) {
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> al(0, 5); // guaranteed unbiased

	Aeroport a(0,0,0);
	int tmp = al(rng);
	switch (tmp) {
	case 0:
		a.set_coord_x(airports[0].get_coord_x());
		a.set_coord_y(airports[0].get_coord_y());
		break;
	case 1:
		a.set_coord_x(airports[1].get_coord_x());
		a.set_coord_y(airports[1].get_coord_y());
		break;
	case 2:
		a.set_coord_x(airports[2].get_coord_x());
		a.set_coord_y(airports[2].get_coord_y());
		break;
	case 3:
		a.set_coord_x(airports[3].get_coord_x());
		a.set_coord_y(airports[3].get_coord_y());
		break;
	case 4:
		a.set_coord_x(airports[4].get_coord_x());
		a.set_coord_y(airports[4].get_coord_y());
		break;
	}
	return a;
}

void doCircle(sf::RectangleShape& plane) {
	plane.move(circle_vector);
	plane.rotate(1);
}

void visualization(std::vector<std::unique_ptr<Avion>>& avions, std::vector<Aeroport>& airports) {
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "My window");
	window.setVerticalSyncEnabled(true);

	sf::Texture backgroundtexture;
	if (!backgroundtexture.loadFromFile("files/fieldtexture.jpg")) {
		std::cerr << "Failed to load texture for background" << std::endl;
		return;
	}
	sf::RectangleShape background(sf::Vector2f(WINDOW_SIZE.x, WINDOW_SIZE.y));
	background.setTexture(&backgroundtexture);

	sf::Texture texture1, texture2;
	sf::RectangleShape sprite1, sprite2, sprite3, sprite4, sprite5;
	texture1.loadFromFile("files/airport.png");
	sprite1.setTexture(&texture1);
	sprite1.setSize(sf::Vector2f(50, 50));
	sprite1.setPosition(sf::Vector2f(airports[0].get_coord_x(), airports[0].get_coord_y()));
	sprite1.setOrigin(sf::Vector2f(25, 25));

	sprite2 = sprite1;
	sprite2.setPosition(sf::Vector2f(airports[1].get_coord_x(), airports[1].get_coord_y()));

	sprite3 = sprite1;
	sprite3.setPosition(sf::Vector2f(airports[2].get_coord_x(), airports[2].get_coord_y()));

	sprite4 = sprite1;
	sprite4.setPosition(sf::Vector2f(airports[3].get_coord_x(), airports[3].get_coord_y()));

	sprite5 = sprite1;
	sprite5.setPosition(sf::Vector2f(airports[4].get_coord_x(), airports[4].get_coord_y()));

	std::cout << "coo airport1 : " << airports[0].get_coord_x() << " " << airports[0].get_coord_y() << std::endl;
	std::cout << "coo airport2 : " << airports[1].get_coord_x() << " " << airports[1].get_coord_y() << std::endl;
	std::cout << "coo airport3 : " << airports[2].get_coord_x() << " " << airports[2].get_coord_y() << std::endl;
	std::cout << "coo airport4 : " << airports[3].get_coord_x() << " " << airports[3].get_coord_y() << std::endl;
	std::cout << "coo airport5 : " << airports[4].get_coord_x() << " " << airports[4].get_coord_y() << std::endl;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}
		window.clear();
		window.draw(sprite1);
		window.draw(sprite2);
		window.draw(sprite3);
		window.draw(sprite4);
		window.draw(sprite5);
		//window.draw(background);
		
		for (auto& avions : avions) {
			window.draw(avions->update_sprite());

		}
		window.display();
	}

}

int main() {

	int nb_avions = 4;

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> randomx(50, WINDOW_SIZE.x-50); // guaranteed unbiased
	std::uniform_int_distribution<int> randomy(50, WINDOW_SIZE.y-50); // guaranteed unbiased
	std::uniform_int_distribution<int> randomp(2, 15); // guaranteed unbiased


	//génération aeroports

	Aeroport Lille(randomx(rng), randomy(rng), randomp(rng));
	Aeroport Paris(randomx(rng), randomy(rng), randomp(rng));
	Aeroport Lyon(randomx(rng), randomy(rng), randomp(rng));
	Aeroport Marseille(randomx(rng), randomy(rng), randomp(rng));
	Aeroport Bordeaux(randomx(rng), randomy(rng), randomp(rng));

	std::vector <Aeroport> airports;

	airports.push_back(std::move(Lille));
	airports.push_back(std::move(Paris));
	airports.push_back(std::move(Marseille));
	airports.push_back(std::move(Lyon));
	airports.push_back(std::move(Bordeaux));


	/*std::cout << "------valeurs coordS------";
	std::cout << Lille.get_coord_x() << std::endl;
	std::cout << Lille.get_coord_y() << std::endl;
	std::cout << Paris.get_coord_x() << std::endl;
	std::cout << Paris.get_coord_y() << std::endl;
	std::cout << "------valeurs coordS------";*/



	constexpr int base_speed = 5;
	std::vector<std::unique_ptr<Avion>> avions;

	sf::Texture planeTexture;
	if (!planeTexture.loadFromFile("files/airplane.png")) {
		std::cerr << "Failed to load texture for planes" << std::endl;
		return EXIT_FAILURE;
	}

	//Avion plane1;//NEED TO PUT IN ALL THE ARGS	

	/*for (int i = 0; i < nb_avions; i++) {
		Aeroport depart = random(airports);
		Aeroport arrivee = random(airports);
		avions.push_back(std::make_unique<Avion>(planeTexture, base_speed * 2, 25.f, depart.get_coord_x(), depart.get_coord_y(), arrivee.get_coord_x(), arrivee.get_coord_y()));
	}*/
	avions.push_back(std::make_unique<Avion>(planeTexture, base_speed * 2, 25.f, Lille.get_coord_x(), Lille.get_coord_y(), Paris.get_coord_x(), Paris.get_coord_y()));
	avions.push_back(std::make_unique<Avion>(planeTexture, base_speed * 2, 25.f, Paris.get_coord_x(), Paris.get_coord_y(), Lille.get_coord_x(), Lille.get_coord_y()));

	std::thread UI(visualization, std::ref(avions), std::ref(airports));

	UI.join();

	return 0;
}