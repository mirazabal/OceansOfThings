#include "sensor_factory.h"
#include <assert.h>

sensor_factory::sensor_factory(){
	static_assert(false, "abstract factory constructor called");
}


sensor_factory::~sensor_factory(){

}



bool sensor_factory::register_sensor(std::string const& name, std::shared_ptr<sensor > sP ){

	if(associative_.find(name) == associative_.end() ){
		associative_.emplace( std::make_pair(name,sP));
		return true;
	}
	else{
		associative_.emplace( std::make_pair(name,sP) );
		return false;
	}
}



bool sensor_factory::unregister_sensor(std::string const& name){
	
	if(associative_.find(name) == associative_.end() ){
		return false;
	}
	else{
		associative_.erase(name);
		return true;
	}


}

std::shared_ptr<sensor> sensor_factory::get_sensor(std::string const& name){
	return associative_.at(name);
}
