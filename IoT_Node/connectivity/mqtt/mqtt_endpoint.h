#ifndef MQTT_ENDPOINT_
#define MQTT_ENDPOINT_


#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif 


#include <string>
#include <memory>

namespace mirazabal
{
namespace mqtt_end
{

class mqtt_endpoint
{
	public:
		mqtt_endpoint();
		~mqtt_endpoint();

		void connect(std::string const & uri);
		void disconnect();
		void emit(std::string const& msg_name, std::string const& msg);

	private:
		struct Impl;
		Impl* pImpl;
};


} // namespace mqtt
} // namespace mirazabal

#endif
