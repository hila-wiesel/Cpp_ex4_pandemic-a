#pragma once

#include "Color.hpp"
#include "City.hpp"
#include <map>
#include <set>
#include <iostream>

namespace pandemic{
	class Board{
		public:
			std :: map < City, Color> color_city;
			std :: map <City, int> disease;
			std :: map <City, bool> research_stations;
			std :: map <City, std::set<City>> ni_city;
			std :: map <Color, bool> medicane;
			
			Board(){};
			~Board(){};
			int& operator[](City city);

			friend std::ostream& operator<< (std::ostream& os, const Board& b);
			bool is_clean();
			void remove_cures();
			
			//getters
			int level_dseases_in(City city);
			Color color_of(City city);
			bool research_stations_in(City city);
			bool medicane_in(City city);
			std::set<City> neighbors_of(City city);
			

	
	
	
	};
}
	