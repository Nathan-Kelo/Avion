#include "aeroport.h"
#include <string>
#include  "nlohmann/json.hpp"
#include <random>

#define max_places 10
#define min_places 5 

using json = nlohmann::json;


void create_aerport() {
	for (int i = 0; i <= 15; i++) {
		json test = {
			{"id", i},
			{"places", min_places + (std::rand() % (max_places - min_places + 1))},
			{"}

		}
	}
}