#include "aeroport.h"
#include <string>


std::string Aeroport::get_name() {
	return this->name;
}

void Aeroport::set_name(string nom) {
	this->name = nom;
}
int Aeroport::set_coord_x(int posx) {
	this->coord_x = posx;
}
int Aeroport::set_coord_y(int posy) {
	this->coord_y = posy;
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

