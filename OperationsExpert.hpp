
#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Player.hpp"
#include "Color.hpp"

namespace pandemic{

    class OperationsExpert : public Player{
        public:
			OperationsExpert(Board borad, City city):Player( borad,  city){};
            Player& build();
            std::string role();
    };
}