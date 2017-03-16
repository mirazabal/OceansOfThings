#include "sensor.h"

#include <assert.h>
//#include <type_traits>
#include <stdexcept>
#include <iostream>

sensor::sensor(){
	
}

sensor::~sensor(){

}

void sensor::get_data_async(std::function<void (const char*, size_t)> const & fp){
	std::runtime_error("Error in inheritance???");
}

