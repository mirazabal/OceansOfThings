#include "sensor.h"

#include <assert.h>
//#include <type_traits>
#include <stdexcept>
#include <iostream>

sensor::sensor(){
	
}

sensor::~sensor(){

}

std::vector<std::string> sensor::get_data(){
//	static_assert(false, "abstract_sensor  get_data called" );
	throw std::runtime_error( " get_gata from sensor called" );
	return std::vector<std::string>();
}


