
#include "iot_node.h"

iot_node::iot_node(std::string const& name){
	name_ = name;
}

iot_node::~iot_node(){

}

std::string iot_node::get_name(){
	return name_;
}

void iot_node::send_data(std::string const& name, std::string const& data){
	endpoint_.emit(name,data);
}

std::shared_ptr<sensor> iot_node::get_sensor(std::string const& sensorName){
	return factory_.get_sensor(sensorName);
}

bool iot_node::add_sensor( std::string const& name, std::shared_ptr<sensor> sP){
	return 	factory_.register_sensor(name, sP);	
}

void iot_node::try_connect(std::string const& uri){
	endpoint_.connect(uri);
}

