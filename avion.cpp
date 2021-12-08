#include "avion.h"
#include <string>

#define CHANCE_DEFAILLANCE 2	//2 chance sur 100 tout les 100km

constexpr int radius_ = 2;
int x_center = 400;
int y_center = 400;


Avion::Avion(sf::Texture Texture) {
	sprite.setTexture(&Texture);
	stop_thread = false;
	initial_clock_ = high_resolution_clock::now();	
	t_ = std::thread(update_avion, std::ref(*this), std::ref(stop_thread));
}

void Avion::circle_trajectory() {
	auto current_clock = high_resolution_clock::now();
	auto dt = (current_clock - initial_clock_).count() / 1e9;
	initial_clock_ = current_clock;
	//Do circles around an aeroprt
	angle_ -= rotation_speed * static_cast<float>(dt);
	x_ = (radius_ * cos(angle_)) + x_center;
	y_ = (radius_ * sin(angle_)) + y_center;
	
}

void Avion::line_trajectory() {
	auto current_clock = high_resolution_clock::now();
	auto dt = (current_clock - initial_clock_).count() / 1e9;
	initial_clock_ = current_clock;
	//Do moving from aeroport 1 to 2
	float distance_x = aeorport_arrive_x - aeorport_depart_x;
	float distance_y = aeorport_arrive_y - aeorport_depart_y;
	float distance_total = sqrt(distance_x * distance_x + distance_y * distance_y);
	x_ += distance_x/distance_total * speed_;
	y_ += distance_y/ distance_total * speed_;	
}

Avion::~Avion() {
	stop_thread = true;
	t_.join();
}

sf::RectangleShape Avion::update_sprite() {
	sprite.setPosition(get_x(), get_y());
	sprite.setRotation(get_angle());
	return sprite;
}


void update_avion(Avion& avion, bool& stop_thread) {
	while (!stop_thread) {
		std::this_thread::sleep_for(1s);
		avion.line_trajectory();
	}
}

const std::string Avion::get_flight_number() { return code_de_vol; }

float Avion::get_speed() { return speed_; }

float Avion::get_altitude() { return altitude; }

float Avion::get_x() { return x_; }

float Avion::get_y() { return y_; }

float Avion::get_angle() { return angle_; }

/*
float Avion::get_niveau_essence() {
	return niveau_essence;
}

int Avion::get_altitude() {
	return altitude;
}

bool Avion::emergency_landing() {
	if (defaillance_avion == true)
		return defaillance_avion;
	else {
		int tmp = rand() % 100;
		defaillance_avion = true ? tmp <= CHANCE_DEFAILLANCE : false;
		return defaillance_avion;		
	}
}

std::string Avion::get_aeroport_arrive() {
	return aeroport_arrive;
}

std::string Avion::get_aeroport_depart() {
	return aeroport_depart;
}*/