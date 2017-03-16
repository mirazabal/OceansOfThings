#ifndef iot_node_h
#define iot_node_h

#include "../IoT_Node/sensors/iot_sensor_factory.h" 
#include "../IoT_Node/connectivity/mqtt/mqtt_endpoint.h"

#include "sensor.h"

#include <memory>
#include <string>

using namespace mirazabal;


class iot_node{

	public:
	 	explicit iot_node(std::string const& name);
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

