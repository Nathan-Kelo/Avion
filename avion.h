#include <string>
#include <vector>
#include "Point3D.h"

class Avion {
private:
	const std::string code_de_vol;
	std::string aeroport_depart;
	std::string aeroport_arrive;
	int altitude;
	float vitesse;
	float niveau_essence;
	float consomation_essence;	
	bool defaillance_avion = false;
public:
	//std::string get_trajectory();
	std::string get_aeroport_depart();
	std::string get_aeroport_arrive();
	float get_vitesse();
	float get_niveau_essence();
	int get_altitude();
	const std::string get_flight_number();
	bool emergency_landing();

};