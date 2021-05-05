#include "Dispatcher.hpp"

	namespace pandemic{

            Dispatcher& Dispatcher::fly_direct(City city){return *this;};
            std::string Dispatcher::role(){return "role";};
	}