#include "callbackAsyncPublish.h"

#include <iostream>


void callbackAsyncPublish::connection_lost(const std::string& cause)
{
	std::cout << "\nConnection lost" << std::endl;
	if (!cause.empty())
		std::cout << "\tcause: " << cause << std::endl;
}

// We're not subscribed to anything, so this should never be called.
void callbackAsyncPublish::message_arrived(const std::string& topic, mqtt::message_ptr msg) { }

void callbackAsyncPublish::delivery_complete(mqtt::idelivery_token_ptr tok)
{
	std::cout << "Delivery complete for token: " << (tok ? tok->get_message_id() : -1) << std::endl;
}

/////////////////////////////////////////////////////////////////////////////


