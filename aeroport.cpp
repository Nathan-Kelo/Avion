#include "aeroport.h"
#include <string>

Aeroport::Aeroport() : coord_x(coordx), coord_y(coordy), max_places(maxplaces) {
	sprite.setSize(sf::Vector2f(50, 50));
	sprite.setTexture(&Texture);
	sprite.setPosition(sf::Vector2f(coord_x, coord_y));
}

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

sf::RectangleShape Aeroport::getSprite() {
	return sprite;
}