#include "aeroport.h"
#include <string>

Aeroport::Aeroport(int coordx, int coordy, int maxplaces) {
	coord_x = coordx;
	coord_y = coordy;
	max_places = maxplaces;
	std::cout << "x : " << coord_x << std:endl;
	std::cout << "y : " << coord_y << std:endl;
}

void Aeroport::set_max_places(int places) {
	this->max_places = places;
}

void Aeroport::avion_arrive(Avion plane) {
	hangar.push_back(plane);
}

void Aeroport::avion_depart(Avion plane) {
	hangar.erase(plane);
}