#include <string>
#include <vector>
#include "Point3D.h"

class Aeroport {
private:
	std::string name;
	int coord_x;
	int coord_y;
	int max_places;
	std::vector<Avion> hangar;
public:
	std::string get_name();
	int get_coord_x();
	int get_coord_y();
	void set_max_places(int places);
	void avion_arrive(Avion plane);
	void avion_depart(Avion plane);

};