#include <string>
#include <vector>
#include "Point3D.h"

class Avion {
private:
	const std::string code_de_vol;
	std::string aeorport_depart;
	std::string aeorport_arrive;
	int altitude;
	float vitesse;
	float niveau_essence;
	float consomation_essence;	
	bool defaillance_avion = false;
public:
	//std::string get_trajectory();
	std::string get_aeorport_depart();
	std::string get_aeorport_arrive();
	float get_vitesse();
	float get_niveau_essence();
	int get_altitude();
	const std::string get_flight_number();
	bool emergency_landing();

};