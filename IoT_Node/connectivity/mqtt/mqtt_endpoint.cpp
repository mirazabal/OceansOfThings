#include "mqtt_endpoint.h"

#include "mqtt/async_client.h"
#include "Paho_MQTT_Unit_Test_Async/callbackAsyncPublish.h"


#include <iostream>

namespace mirazabal
{
namespace mqtt_end
{

	struct mqtt_endpoint::Impl
	{
		Impl(): client_{nullptr}
		{

		}

		callbackAsyncPublish cb;
		std::unique_ptr<mqtt::async_client> client_;
	};

	mqtt_endpoint::mqtt_endpoint()  
	{
		pImpl = new Impl();
	}

	mqtt_endpoint::~mqtt_endpoint()
	{
		if(pImpl != nullptr){
			delete pImpl;
			pImpl = nullptr;
		}
	}

	void mqtt_endpoint::connect(std::string const & uri)
	{
		if(pImpl->client_ == nullptr)
			pImpl->client_ = std::make_unique<mqtt::async_client>(uri, "client_id");

		pImpl->client_->set_callback( pImpl->cb );		
	
		mqtt::itoken_ptr conntok = pImpl->client_->connect();
		std::cout << "Waiting for the connection..." << std::flush;
		conntok->wait_for_completion();
		std::cout << "OK" << std::endl;

	}

	void mqtt_endpoint::disconnect(){
		auto conntok = pImpl->client_->disconnect();
		conntok->wait_for_completion();
	}

	void mqtt_endpoint::emit(std::string const& msg_name, std::string const& msg)
	{
		mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(msg);
		// First use a message pointer.
		std::cout << "Sending message..." << std::flush;
		const int QOS = 1;
		pubmsg->set_qos(QOS);
		const int TIMEOUT = 10000;
		pImpl->client_->publish(msg_name, pubmsg)->wait_for_completion(TIMEOUT);
		std::cout << "OK" << std::endl;
	}
} // namespace mqtt
} // namespace mirazabal

