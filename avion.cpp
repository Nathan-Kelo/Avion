#include "avion.h"
#include <cmath>

constexpr int radius_ = 5;
constexpr float PI_F = static_cast<float>(M_PI);

void update_avion(Avion& avion, bool& stop_thread) {
	while (!stop_thread) {
		std::this_thread::sleep_for(1s);
		if (avion.get_distance_parcouru_trajet() > avion.get_distance_total())
		{
			avion.circle_trajectory();
		}
		else avion.line_trajectory();
	}
}


Avion::Avion(sf::Texture &Texture, float speed,float init_angle, float aeroport_depart_x, float aeroport_depart_y, float aeroport_arrive_x, float aeroport_arrive_y) :
	aeroport_depart_x(aeroport_depart_x), aeroport_depart_y(aeroport_depart_y),
	aeroport_arrive_x(aeroport_arrive_x), aeroport_arrive_y(aeroport_arrive_y),
	x_(aeroport_depart_x), y_(aeroport_depart_y),angle_(init_angle *PI_F/180.f),
	speed_(speed), rotation_speed(speed / 2.f*PI_F*radius_),
	distance_parcouru_trajet(0),distance_total(0)
{	
	sprite.setSize(sf::Vector2f(50, 50));
	sprite.setTexture(&Texture);	
	sprite.setPosition(sf::Vector2f(aeroport_depart_x,aeroport_depart_y));
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
	x_ = (radius_ * cos(angle_)) + aeroport_arrive_x;
	y_ = (radius_ * sin(angle_)) + aeroport_arrive_y;
	//std::cout << "--------We are doing a circle trajectory--------\n\tx :" << x_ << "\n\ty :" << y_ << std::endl;
}

void Avion::line_trajectory() {
	auto current_clock = high_resolution_clock::now();
	auto dt = (current_clock - initial_clock_).count() / 1e9;
	initial_clock_ = current_clock;
	//Do moving from aeroport 1 to 2
	float distance_x = aeroport_arrive_x - aeroport_depart_x;
	float distance_y = aeroport_arrive_y - aeroport_depart_y;
	distance_total = sqrt(distance_x * distance_x + distance_y * distance_y);
	x_ += distance_x / distance_total * speed_;
	y_ += distance_y / distance_total * speed_;
	distance_parcouru_trajet = sqrt((x_-aeroport_depart_x) * (x_ - aeroport_depart_x) + (y_ - aeroport_depart_y) * (y_ - aeroport_depart_y));

	if(distance_x<0){
		angle_ = 180+acos(distance_y / std::sqrt(std::pow(distance_x, 2) + std::pow(distance_y, 2))) / (PI_F / 180.f);
	}
	else {
		angle_ = 180-acos(distance_y / std::sqrt(std::pow(distance_x, 2) + std::pow(distance_y, 2))) / (PI_F / 180.f);
	}

	//std::cout << "--------We are doing a line trajectory--------\n\tx :" << x_ << "\n\ty :" << y_ << std::endl;
}
Avion::~Avion() {
	stop_thread = true;
	t_.join();
}

sf::RectangleShape Avion::update_sprite() {
	sprite.setPosition(sf::Vector2f(get_x(), get_y()));
	sprite.setRotation(get_angle());
	return sprite;
}




const std::string Avion::get_flight_number() { return code_de_vol; }

float Avion::get_speed() { return speed_; }

float Avion::get_altitude() { return altitude; }

float Avion::get_x() { return x_; }

float Avion::get_y() { return y_; }

float Avion::get_aeroport_arrive_x() { return aeroport_arrive_x; }

float Avion::get_aeroport_arrive_y() { return aeroport_arrive_y; }

float Avion::get_aeroport_depart_x() { return aeroport_depart_x; }

float Avion::get_aeroport_depart_y() { return aeroport_depart_y; }

float Avion::get_angle() { return angle_; }

float Avion::get_distance_parcouru_trajet() { return distance_parcouru_trajet; }

float Avion::get_distance_total() { return distance_total; }

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