#ifndef NMEA_0183_SENSOR_H
#define NMEA_0183_SENSOR_H

#include "../sensor.h"
#include <memory>

class NMEA_0183_sensor : public sensor 
{
	public:
		NMEA_0183_sensor();
		virtual ~NMEA_0183_sensor();

		void get_data_async(std::function<void ( const char *, size_t)> const& ) override;
	private:
		struct Impl;
		std::unique_ptr<Impl> pImpl;

};

#endif

