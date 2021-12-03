#include "avion.h"
#include <string>

#define CHANCE_DEFAILLANCE 2	//2 chance sur 100 tout les 100km

const std::string Avion::get_flight_number() {
	return code_de_vol;
}

float Avion::get_vitesse() {
	return vitesse;
}

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

std::string Avion::get_aeorport_arrive() {
	return aeorport_arrive;
}

std::string Avion::get_aeorport_depart() {
	return aeorport_depart;
}