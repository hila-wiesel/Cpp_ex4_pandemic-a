#include "Board.hpp"
using namespace std;
namespace pandemic{
	
		int& Board::operator[](City city){
			return this -> disease[city];
		}
		bool Board ::is_clean(){return false;};
		void Board ::remove_cures(){};
		ostream& operator<< (std::ostream& os, const Board& b){return os;};
		
		int Board ::level_dseases_in(City city){return 5;};
		Color Board ::color_of(City city){
			return Color::Black;
		
			}
		bool Board ::research_stations_in(City city){return false;};
		bool Board ::medicane_in(City city){return false;};
		set<City> Board ::neighbors_of(City city){
			return this->ni_city[city];};
			
	
}
		
		