#ifndef iot_node_h
#define iot_node_h


#include "sensor.h"
#include "iot_sensor_factory.h" 

#include "mqtt_endpoint.h"


#include <string>
#include <memory>

class iot_node{

	public:
		iot_node(std::string const& name);
		~iot_node(); 	

		std::string get_name();
		bool add_sensor( std::string const& name, std::shared_ptr<sensor> sP);
		std::shared_ptr<sensor> get_sensor(std::string const& sensorName);
		void try_connect(std::string const& uri);
		void send_data(std::string const& name, std::string const& data);

	private:
		iot_sensor_factory factory_;
		std::string name_;

		mirazabal::mqtt_end::mqtt_endpoint endpoint_;

};

#endif

