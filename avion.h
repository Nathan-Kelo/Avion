#pragma once 
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>


using std::chrono::duration;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using namespace std::chrono_literals;


class Avion {
private:
	std::thread t_;
	bool stop_thread = false ;
	high_resolution_clock::time_point initial_clock_;
	sf::RectangleShape sprite;
	
	const std::string code_de_vol;
	float x_ = 0.;
	float y_ = 0.;
	float altitude = 0.;
	float speed_ = 0.;
	float rotation_speed = 0.;
	float angle_ = 0.;
	float aeorport_depart_x = 0.;
	float aeorport_depart_y = 0.;
	float aeorport_arrive_x = 0.;
	float aeorport_arrive_y = 0.;
	/*	
	float niveau_essence;
	float consomation_essence;	
	bool defaillance_avion = false;*/
public:
	Avion(sf::Texture Texture);
	/*Draws a cirlce around a designated center
	*/
	void circle_trajectory();
	void line_trajectory();
	sf::RectangleShape update_sprite();
	float get_speed();
	float get_altitude();
	float get_angle();
	float get_x();
	float get_y();	
	const std::string get_flight_number();
	/*std::string get_aeroport_depart();
	std::string get_aeroport_arrive();
	
	float get_niveau_essence();
	
	
	bool emergency_landing();*/
	

};