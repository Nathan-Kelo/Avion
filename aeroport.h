#include <string>
#include <vector>
#include "SFML/Graphics.hpp"

class Aeroport {
private:
	std::string name;
	int coord_x;
	int coord_y;
	int max_places;
	sf::RectangleShape sprite;
	std::vector<Avion> hangar;
public:
	Aeroport(sf::Texture& Texture, int coordx, int coordy, int maxplaces) {}
	std::string get_name();
	//void set_name(std::string nom);
	void set_coord_x(int posx);
	void set_coord_y(int posy);
	int get_coord_x() {
		return coord_x;
		};
	int get_coord_y() {
		return coord_y;
		};
	void set_max_places(int places);
	void avion_arrive(Avion plane);
	void avion_depart(Avion plane);
	sf::RectangleShape getSprite();

};