
#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Player.hpp"
#include "Color.hpp"

namespace pandemic{

    class GeneSplicer : public Player{
        public:
			GeneSplicer(Board board, City city):Player(board, city){};
            void discover_cure(Color  color);
            std::string role();
    };
}