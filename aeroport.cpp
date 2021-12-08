#include "aeroport.h"
#include <string>


std::string Aeroport::get_name() {
	return name;
}

int Aeroport::get_coord_x() {
	return coord_x;
}

int Aeroport::get_coord_y() {
	return coord_y;
}

void Aeroport::set_max_places(int places) {
	max_places = places;
}

void Aeroport::avion_arrive(Avion plane) {
	hangar.push_back(plane);
}

void Aeroport::avion_depart(Avion plane) {
	hangar.erase(plane);
}