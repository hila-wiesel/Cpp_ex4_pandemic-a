
#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Player.hpp"
#include "Color.hpp"

namespace pandemic{

    class Scientist : public Player{
        public:
			Scientist(Board board, City city, int n):Player(board, city){};

            void discover_cure(Color  color);
            std::string role();
    };
}