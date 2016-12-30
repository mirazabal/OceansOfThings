#ifndef CALLBACK_ASYNC_PUBLISH_H
#define CALLBACK_ASYNC_PUBLISH_H

#include "mqtt/callback.h"

/**
 * A callback class for use with the main MQTT client.
 */

class callbackAsyncPublish : public mqtt::callback
{
public:
	void connection_lost(const std::string& cause) override;
	// We're not subscribed to anything, so this should never be called.
	void message_arrived(const std::string& topic, mqtt::message_ptr msg) override;
	void delivery_complete(mqtt::idelivery_token_ptr tok) override;

};

#endif

