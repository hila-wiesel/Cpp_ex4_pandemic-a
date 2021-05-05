#pragma once
#include "City.hpp"
#include "Board.hpp"
#include "Color.hpp"
#include <string>
#include <set>
#include <iostream>

namespace pandemic{
		class Player{
			public:
				Player(Board board, City city){}
				~Player(){}
				Player& drive(City city);
				Player& fly_direct(City  city);
				Player& fly_charter(City  city);
				Player& fly_shuttle(City  city);
				Player& build(City  city);
				Player& discover_cure(Color  color);
				Player& treat(City  city);
				std :: string role();
				Player& take_card(City  city);
				
		};
}
			
			