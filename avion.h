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
	float aeroport_depart_x = 0.;
	float aeroport_depart_y = 0.;
	float aeroport_arrive_x = 0.;
	float aeroport_arrive_y = 0.;				
	float distance_parcouru_trajet = 0.;		//Distance parcouru par l'avion
	float distance_total = 0.;					//Distance entre les deux aeroports
	/*	
	float niveau_essence;
	float consomation_essence;	
	bool defaillance_avion = false;*/
public:
	Avion(const sf::Texture Texture,float speed,float aeroport_depart_x, float aeroport_depart_y, float aeroport_arrive_x,float aeroport_arrive_y);
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
	float get_aeroport_arrive_x();
	float get_aeroport_arrive_y();
	float get_aeroport_depart_x();
	float get_aeroport_depart_y();
	float get_distance_parcouru_trajet();
	float get_distance_total();
	const std::string get_flight_number();
	~Avion();
	/*std::string get_aeroport_depart();
	std::string get_aeroport_arrive();
	
	float get_niveau_essence();
	
	
	bool emergency_landing();*/
	

};