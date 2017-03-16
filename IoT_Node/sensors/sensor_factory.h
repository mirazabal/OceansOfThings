#ifndef sensor_factory_h
#define sensor_factory_h

#include "sensor.h"

#include <unordered_map>
#include <memory>


class sensor_factory{
public:
	sensor_factory();
 	virtual ~sensor_factory();

	bool register_sensor(std::string const& name, std::shared_ptr<sensor > sP );
	bool unregister_sensor(std::string const& name);
	std::shared_ptr<sensor> get_sensor(std::string const& name);
private:
	std::unordered_map<std::string, std::shared_ptr< sensor > > associative_;	

};

#endif

